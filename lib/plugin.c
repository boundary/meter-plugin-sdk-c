//
// Copyright 2016 BMC Software, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <assert.h>
#include <string.h>
#include <unistd.h>
#include "plugin.h"

/** \brief Initializes the members of the meter_plugin structure
 *
 */
static void plugin_initialize(meter_plugin_t *plugin) {
    memset(plugin, '\0', sizeof(meter_plugin_t));
}

/** \brief Allocates a plugin structure and initializes
 *
 */
meter_plugin_t *plugin_create() {
    meter_plugin_t *plugin = malloc(sizeof(meter_plugin_t));
    assert(plugin);
    plugin_initialize(plugin);
    return plugin;
}

/** \brief Calls the plugin provided plugin init method if registered
 *
 *  @param plugin Pointer to meter_plugin structure
 */
plugin_result_t plugin_INITIALIZE(meter_plugin_t *plugin) {
    plugin_result_t result = PLUGIN_SUCCEED;

    assert(plugin);

    // If an initialization method has been registered call it
    if (plugin->initialize_cb && plugin->initialize_cb(plugin) == PLUGIN_FAIL) {
            fprintf(stderr, "Plugin initialization function failed\n");
            result = PLUGIN_FAIL;
    }
    return result;
}

/** \brief Calls the plugin provided plugin start method if registered
 *
 *  @param plugin Pointer to meter_plugin structure
 */
plugin_result_t plugin_START(meter_plugin_t *plugin) {
    plugin_result_t result = PLUGIN_SUCCEED;

    assert(plugin);

    // If an start method has been registered call it
    if (plugin->start_cb && plugin->start_cb(plugin) == PLUGIN_FAIL) {
            fprintf(stderr, "Plugin start function failed\n");
            result = PLUGIN_FAIL;
    }
    return result;
}

/** \brief Create collectors for each of the parameter items
 *
 *  @param plugin Pointer to meter_plugin structure
 */
int plugin_COLLECTORS_CREATE(meter_plugin_t *plugin) {
    plugin_result_t result = PLUGIN_SUCCEED;

    assert(plugin);
    assert(plugin->parameters);

    size_t size = plugin->parameters->size;
    collector_ptr_t *collectors = malloc(sizeof(collector_ptr_t) * size);
    assert(collectors);

    plugin_parameters_t *parameters = plugin->parameters;
    for (int i = 0; i < size; i++) {
        parameter_item_t *items = parameters->items[i];
        collector_t * collector = collector_create(items);
        plugin->collector_initialize_cb(plugin, collector);
        collectors[i] = collector;
    }

    plugin->collectors.list = collectors;
    plugin->collectors.size = size;

    return result;
}

/** \brief Calls the collector initialization method on each of the collectors
 *
 *  @param plugin Pointer to meter_plugin structure
 */
plugin_result_t plugin_COLLECTORS_INITIALIZE(meter_plugin_t *plugin) {
    plugin_result_t result = PLUGIN_SUCCEED;

    assert(plugin);

    size_t size = plugin->collectors.size;
    collector_ptr_t *collectors = plugin->collectors.list;

    for (size_t i = 0; i < size; i++) {
        collector_t *collector = collectors[i];
        if (collector_initialize(collector) == PLUGIN_FAIL) {
            result = PLUGIN_FAIL;
            break;
        }
    }
    return result;
}

/** \brief Calls the collector initialization method on each of the collectors
 *
 *  @param plugin Pointer to meter_plugin structure
 */
plugin_result_t plugin_COLLECTORS_START(meter_plugin_t *plugin) {
    plugin_result_t result = PLUGIN_SUCCEED;

    assert(plugin);

    size_t size = plugin->collectors.size;
    collector_ptr_t *collectors = plugin->collectors.list;

    for (size_t i = 0; i < size; i++) {
        collector_t *collector = collectors[i];
        collector_start(collector);
    }

    return result;
}

/** \brief Read and parse the plugin parameters
 *
 *  @param plugin Pointer to meter_plugin structure
 */
plugin_result_t plugin_PARAMETERS_LOAD(meter_plugin_t *plugin) {
    plugin_result_t result = PLUGIN_SUCCEED;

    assert(plugin);
    // Load the plugin configuration from "param.json"
    plugin_parameters_t *parameters = parameter_load(PARAMETERS_DEFAULT_PATH);
    if (parameters) {
        plugin->parameters = parameters;
    }
    else {
        fprintf(stderr, "Unable to load plugin parameters\n");
        result = PLUGIN_FAIL;
    }

    return result;
}

/** \brief Calls the plugin provided plugin start method if registered
 *
 *  @param plugin Pointer to meter_plugin structure
 */
plugin_result_t plugin_PARAMETERS_LOADED(meter_plugin_t *plugin) {
    plugin_result_t result = PLUGIN_SUCCEED;

    assert(plugin);

    // If an parameter method has been registered call it
    if (plugin->parameters_cb && plugin->parameters_cb(plugin) == PLUGIN_FAIL) {
        fprintf(stderr, "Plugin parameters function failed\n");
        result = PLUGIN_FAIL;
    }
    return result;
}

/** \break Run the plugin collection
 *
 *  @param plugin Pointer to meter_plugin structure
 */
plugin_result_t plugin_RUN(meter_plugin_t *plugin) {
    plugin_result_t result = PLUGIN_SUCCEED;

    size_t size = plugin->collectors.size;
    int collect_measurements = 1;

    while (collect_measurements) {
        // Loop through the collectors and call eaches respective collection method
        for (int i = 0; i < size; i++) {
            collector_t *collector = plugin->collectors.list[i];
            if (collector_collect(collector) == PLUGIN_FAIL) {
                collect_measurements = 0;
                break;
            }
        }
        sleep(1);
    }
    return result;
}

// Define the states of the plugin at run time
enum plugin_states {
    PLUGIN_INITIALIZE,
    PLUGIN_PARAMETERS_LOAD,
    PLUGIN_PARAMETERS_LOADED,
    PLUGIN_COLLECTORS_CREATE,
    PLUGIN_COLLECTORS_INITIALIZE,
    PLUGIN_START,
    PLUGIN_COLLECTORS_START,
    PLUGIN_RUN,
    PLUGIN_EXIT,
    PLUGIN_ERROR
};

// Define a type for our plugin states
typedef enum plugin_states plugin_state_t;

// Utility macro to drive our state machine
#define NEXT_PLUGIN_STATE(FUNCTION, SUCCESS, FAILURE) (FUNCTION) == PLUGIN_SUCCEED ? (SUCCESS) : (FAILURE)

/** /brief Main plugin function for processing measurements. Implemented as a state machine
 *
 */
plugin_result_t plugin_run(meter_plugin_t *plugin) {
    plugin_result_t result = PLUGIN_SUCCEED;
    plugin_state_t state = PLUGIN_INITIALIZE;

    while (state != PLUGIN_EXIT) {
        switch (state) {
            case PLUGIN_INITIALIZE:
                state = NEXT_PLUGIN_STATE(plugin_INITIALIZE(plugin), PLUGIN_PARAMETERS_LOAD, PLUGIN_ERROR);
                break;
            case PLUGIN_PARAMETERS_LOAD:
                state = NEXT_PLUGIN_STATE(plugin_PARAMETERS_LOAD(plugin), PLUGIN_PARAMETERS_LOADED, PLUGIN_ERROR);
                break;
            case PLUGIN_PARAMETERS_LOADED:
                state = NEXT_PLUGIN_STATE(plugin_PARAMETERS_LOADED(plugin), PLUGIN_COLLECTORS_CREATE, PLUGIN_ERROR);
                break;
            case PLUGIN_COLLECTORS_CREATE:
                state = NEXT_PLUGIN_STATE(plugin_COLLECTORS_CREATE(plugin), PLUGIN_COLLECTORS_INITIALIZE, PLUGIN_ERROR);
                break;
            case PLUGIN_COLLECTORS_INITIALIZE:
                state = NEXT_PLUGIN_STATE(plugin_COLLECTORS_INITIALIZE(plugin), PLUGIN_START, PLUGIN_ERROR);
                break;
            case PLUGIN_START:
                state = NEXT_PLUGIN_STATE(plugin_START(plugin), PLUGIN_COLLECTORS_START, PLUGIN_ERROR);
                break;
            case PLUGIN_COLLECTORS_START:
                state = NEXT_PLUGIN_STATE(plugin_COLLECTORS_START(plugin), PLUGIN_RUN, PLUGIN_ERROR);
                break;
            case PLUGIN_RUN:
                state = NEXT_PLUGIN_STATE(plugin_RUN(plugin), PLUGIN_START, PLUGIN_EXIT);
                break;
            case PLUGIN_ERROR:
                state = PLUGIN_EXIT;
                break;
            default:
                break;
        }
    }
}
