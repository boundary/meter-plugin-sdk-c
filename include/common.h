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
#ifndef METER_PLUGIN_COMMON_H
#define METER_PLUGIN_COMMON_H

// Define result codes
enum plugin_result {
    PLUGIN_SUCCEED,
    PLUGIN_FAIL
};

// Define a type of the result codes
typedef enum plugin_result plugin_result_t;

// Utility function for generating random numbers
double rand_range(int min, int max);

// Macro to log a string, line of code, and function name
#define PLUGIN_FUNCTION_NAME(NAME) fprintf(stderr, "%s: line: %d, %s\n",(NAME), __LINE__, __PRETTY_FUNCTION__);

#endif //METER_PLUGIN_COMMON_H
