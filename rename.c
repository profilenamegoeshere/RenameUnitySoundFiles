#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

int main(){
    printf("is printing even working?\n");
    int numberOfNames = 0;

    // Opens Sounds folder
    char* dirPath = "./Sounds";
    DIR* directory = opendir(dirPath);
    if(directory==NULL){
        printf("Can't open directory");
        return 1;
    }

    // Opens "curr_names.txt"
    char* currNamesPath = "curr_names.txt";
    FILE* currNamesList = fopen(currNamesPath, "w");
    if(currNamesList==NULL){
        printf("Can't open new names list");
        return 2;
    }

    // Loops through sounds and gets names of all files -> curr_names.txt
    struct dirent* entry;
    while((entry = readdir(directory))!=NULL){
        if(strcmp(entry->d_name, ".")==0||strcmp(entry->d_name, "..")==0){
            continue;
        }
        fprintf(currNamesList, "%s\n", entry->d_name);
        numberOfNames++;
    }

    // Opens "new_names.txt", reopens curr_names as read
    char* newNamesPath = "new_names.txt";
    FILE* newNamesList = fopen(newNamesPath, "w");
    if(newNamesList==NULL){
        printf("Couldn't open new names list");
        return 3;
    }
    fclose(currNamesList);
    currNamesList = fopen(currNamesPath, "r");
    char* currNameString = malloc(128*sizeof(char));
    int fileNumber = 0;
    // create new names
    while(fgets(currNameString, 64,currNamesList)){
        fileNumber = atoi(currNameString);
        if(fileNumber<=8){
            fprintf(newNamesList,currNameString);
        } else {
            fileNumber = fileNumber - 1;
            strncpy(currNameString, currNameString+2,64);
            fprintf(newNamesList,"%02d%s", fileNumber,currNameString);
        }
    }

    // Reopen newNames, opens new sounds directory
    char* dirTempPath = "./SoundsTemp";
    DIR* directoryTemp = opendir(dirTempPath);
    if(directoryTemp==NULL){
        printf("Can't open temp directory");
        return 4;
    }
    fclose(newNamesList);
    newNamesList = fopen(newNamesPath,"r");
    char* newNameString = malloc(128*sizeof(char));
    char* soundPath = malloc(128*sizeof(char));
    // actually renaming *sweating*
    while((entry = readdir(directoryTemp))!=NULL){
        if(strcmp(entry->d_name, ".")==0||strcmp(entry->d_name, "..")==0){
            continue;
        }
        strcpy(newNameString,"SoundsTemp/");    // newname = SoundsTemp/
        strcpy(soundPath,"SoundsTemp/");    // soundpath = SoundsTemp/
        fgets(currNameString,64,newNamesList);  // curr = *name*\n
        currNameString[strcspn(currNameString, "\n")] = '\0';   // curr = *name*
        strncat(newNameString,currNameString,64);   // newname = SoundsTemp/*name*
        strncat(soundPath,entry->d_name,64);    // soundpath = SoundsTemp/*oldname*
        printf("%s | becomes %s\n", soundPath, newNameString);
        if(rename(soundPath,newNameString)!=0){ // rename old to new
            printf("Couldn't rename %s\n", entry->d_name);
            printf("%s\n", strerror(errno));
        }
    }

    closedir(directory);
    fclose(currNamesList);
    fclose(newNamesList);
    free(currNameString);
    free(soundPath);
    return 0;
}