//
//  fileutils.cpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 7/19/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#include "fileutils.h"

// done in C for performance reason

std::string file_reader(const char* filename) {
    
    std::string fileString;
    char* buffer;
    long fileLength = 0;
    
    //using fopen to do the opening of files
    FILE* fileFD;
    
    fileFD = fopen(filename, "r");
    
    if (fileFD == NULL) {
        fileString = "empty file";
        return fileString;
    }
    fseek(fileFD, 0, SEEK_END);
    fileLength = ftell(fileFD);
    fseek(fileFD, 0, SEEK_SET);
    
    buffer = (char*) malloc(fileLength + 1);
    
    if (buffer) {
        fread(buffer, 1, fileLength, fileFD);
    }
    buffer[fileLength] = '\0';
    
    fileString = buffer;
    free(buffer);
    
    
    fclose(fileFD);
    return fileString;
}
