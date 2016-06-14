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
#ifndef METER_PLUGIN_PARAM_H
#define METER_PLUGIN_PARAM_H

#include <jansson.h>

// forward declarations
struct meter_plugin;

#define PARAMETER_MAX_STRING 128

#define PARAMETERS_DEFAULT_PATH "./param.json"

typedef char param_boolean_t;
typedef long long param_integer_t;
typedef double param_real_t;
typedef const char * param_string_t;

typedef json_t parameter_item_t;
typedef parameter_item_t * parameter_item_ptr_t;

struct plugin_parameters {
    size_t size;
    parameter_item_ptr_t *items;
};

typedef struct plugin_parameters plugin_parameters_t;

plugin_parameters_t * parameter_load(const char *path);

void parameter_initialize(struct meter_plugin *plugin);

//
// Public API
//
param_boolean_t parameter_get_boolean(parameter_item_t *item, const char *key);
param_integer_t parameter_get_integer(parameter_item_t *item, const char *key);
param_real_t parameter_get_real(parameter_item_t *item, const char *key);
param_string_t parameter_get_string(parameter_item_t *item, const char *key);


#endif //METER_PLUGIN_PARAM_H
