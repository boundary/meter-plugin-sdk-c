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
#ifndef METER_PLUGIN_COLLECTOR_H
#define METER_PLUGIN_COLLECTOR_H

#include "measurement.h"
#include "param.h"
#include "common.h"

// Defines the size of the collector name
#define COLLECTOR_NAME_SIZE 32


// Forward declaration
struct collector;

/** \brief Function pointer type for initializing a collector
 *
 */
typedef plugin_result_t (*collector_init_cb)(struct collector *collector);

/** \brief Function pointer type for starting a collector
 *
 */
typedef plugin_result_t (*collector_start_cb)(struct collector *collector);

/** \brief Function pointer type for collecting measurements by a collector
 *
 */
typedef plugin_result_t (*collector_collect_cb)(struct collector *collector);

/** \brief Structure that implements a meter plugin collector
 *
 */
struct collector {
    char name[COLLECTOR_NAME_SIZE];
    parameter_item_t * item;

    void * data;

    measurement_send_func send_measurement;

    collector_init_cb initialize_cb;
    collector_start_cb start_cb;
    collector_collect_cb collect_cb;
};

// Define type for collector
typedef struct collector collector_t;
// Define type for pointer to a collector
typedef collector_t * collector_ptr_t;

// Structure to contain a list of collectors
struct collector_list {
    collector_ptr_t *list;
    size_t size;
};

// Defined a type that contains a list of collectors
typedef struct collector_list collector_list_t;

//
// Private API
//

// Calls the collectors initialize function
plugin_result_t collector_initialize(collector_t *collector);

// Calls the collectors start function
plugin_result_t collector_start(collector_t *collector);

// Calls the collectors collect function
plugin_result_t collector_collect(collector_t *collector);

//
// Public API
//

// Allocates a collector structure instance
collector_t * collector_create(parameter_item_t *item);

#endif //METER_PLUGIN_COLLECTOR_H
