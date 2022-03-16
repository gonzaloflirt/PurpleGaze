#include "usb_names.h"

#define MIDI_NAME {'P', 'u', 'r', 'p', 'l', 'e', ' ', 'G', 'a', 'z', 'e'}
#define MIDI_NAME_LEN 11

struct usb_string_descriptor_struct usb_string_product_name = {
        2 + MIDI_NAME_LEN * 2,
        3,
        MIDI_NAME
};

