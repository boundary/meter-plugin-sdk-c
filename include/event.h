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
#ifndef METER_PLUGIN_EVENT_H
#define METER_PLUGIN_EVENT_H

#include <time.h>

// ToDo capability to override or make dynamic

#define EVENT_MESSAGE_SIZE 255
#define EVENT_SOURCE_SIZE 255
#define EVENT_SENDER_SIZE 255
#define EVENT_TAGS_SIZE 1024
#define EVENT_APP_DATA_TYPE_SIZE 32
#define EVENT_APP_DATA_SIZE 1024

#define EVENT_STRING_M

// Define the different event types
enum event_type {
    INFO,
    WARN,
    ERROR,
    CRITICAL
};

// Define type for event types
typedef enum event_type event_type_t;

// Define a structure to hold our event data
struct event {
    char message[EVENT_MESSAGE_SIZE+1];
    event_type_t type;
    char source[EVENT_SOURCE_SIZE+1];
    char sender[EVENT_SENDER_SIZE+1];
    time_t date;
    char tags[EVENT_TAGS_SIZE];
    char app_data_type[EVENT_APP_DATA_TYPE_SIZE];
    char app_data[EVENT_APP_DATA_SIZE];
};

// Define type for our event
typedef struct event EVENT;

// Simple implementation to send an event need by a plugin
void event_send(const char *message, event_type_t type, const char *tags);


#endif //METER_PLUGIN_EVENT_H
