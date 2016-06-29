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

#include <stdio.h>
#include "event.h"

static const char * event_type_strings[] = {
    "info",
    "warn",
    "error",
    "critical"
};

/** \brief Translates the enumeration to string value
 *
 */
static const char * event_type_to_string(event_type_t type) {
    return event_type_strings[type];
}

/** \brief Sends an event from the plugin
 *
 */
void event_send(const char *message, event_type_t type, const char *tags) {
    printf("bevent:%s|t:%s|tags:%s\n", message, event_type_to_string(type), tags);
}
