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
#include "collector.h"

/** @brief Calls our collectors initialize method
 *
 *  @param collector Instance of a collector to call its initialize method up
 */
plugin_result_t collector_initialize(collector_t *collector) {
    plugin_result_t result = PLUGIN_SUCCEED;
    assert(collector);
    if (collector->initialize_cb && collector->initialize_cb(collector) == PLUGIN_FAIL) {
        fprintf(stderr, "Collector initialize function failed!\n");
        result = PLUGIN_FAIL;
    }
    return result;
}

/** \brief Calls our collectors start method
 *
 *  @param collector Instance of a collector to call its start method up
 */
plugin_result_t collector_start(collector_t *collector) {
    plugin_result_t result = PLUGIN_SUCCEED;

    assert(collector);

    if (collector->start_cb && collector->start_cb(collector) == PLUGIN_FAIL) {
        fprintf(stderr, "Collector start function failed!\n");
        result = PLUGIN_FAIL;
    }
    return result;
}

/** \brief Calls our collectors collect method
 * \typedef collector_t
 *
 *  @param collector Instance of a collector to call its collect method
 */
plugin_result_t collector_collect(collector_t *collector) {
    plugin_result_t result = PLUGIN_SUCCEED;

    assert(collector);

    if (collector->collect_cb && collector->collect_cb(collector) == PLUGIN_FAIL) {
        fprintf(stderr, "Collector collect function failed!\n");
        result = PLUGIN_FAIL;
    }
    return result;
}


/**
 * \brief Create a collector object
 *
 *  @param collector Instance of a collector to call its collect method
 */
collector_t *collector_create(parameter_item_t *item) {
    collector_t *collector = malloc(sizeof(collector_t));
    assert(collector);

    // Initialize the memory associated with the structure
    memset(collector,'\0', sizeof(collector_t));
    collector->item = item;

    // Default the sink to standard out, specific plugins can override in the collector init method
    collector->send_measurement = measurement_get_sink(STDOUT);

    return collector;
}
