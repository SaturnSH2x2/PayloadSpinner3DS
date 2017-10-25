#include <stdlib.h>
#include <3ds.h>
#include <jansson.h>

#include "jsondata.h"
#include "pp2d/pp2d.h"

#define MAXSIZE 255

char** titleArray;
char** descArray;

int arrSize;

void u() {
    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
}

int loadJsonData(char* error, char** fileList) {
    int i;
    
    json_t* root;
    json_t* value;
	json_t* sv;
    json_error_t err;
    
    root = json_load_file("/3ds/data/PayloadSpinner3DS/data.json", 0, &err);
    if (root == NULL) {
        snprintf(error, MAXSIZE, "json error: %s", err.text);
        json_decref(root);
        return -1;
    }
    
    if (json_is_object(root) == 0) {
        snprintf(error, MAXSIZE, "json error: root isn't object");
        json_decref(root);
        return -1;
    }

    arrSize = sizeof(fileList) / sizeof(*fileList);
    titleArray = malloc(arrSize * sizeof(*titleArray));
    descArray = malloc(arrSize * sizeof(*descArray));
    printf("memory allocated\n");
    u();
    
    for (i = 0; i < arrSize; i++) {
		titleArray[i] = malloc(MAXSIZE * sizeof(char*));
		descArray[i] = malloc(MAXSIZE * sizeof(char*));
		
		value = json_object_get(root, fileList[i]);
		if (value == NULL) {
			snprintf(titleArray[i], MAXSIZE, fileList[i]);
			snprintf(descArray[i], MAXSIZE, fileList[i]);
			pp2d_load_texture_png(i, "romfs:/assets/noimg.png");
		} else {
			sv = json_object_get(value, "display-name");
			snprintf(titleArray[i], MAXSIZE, json_string_value(sv));
			
			sv = json_object_get(value, "description");
			snprintf(descArray[i], MAXSIZE, json_string_value(sv));
			
			sv = json_object_get(value, "image");
			pp2d_load_texture_png(i, json_string_value(sv));
		}
	}
	
	json_decref(sv);
	json_decref(value);
	json_decref(root);
	
	for (i = 0; i < arrSize; i++) {
		printf("Title %d: %s\n", i, titleArray[i]);
		printf("Description %d: %s\n", i, descArray[i]);
	}
	
	return 0;
}
			