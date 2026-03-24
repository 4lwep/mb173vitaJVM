#include "init.h"

//MaHashMap *method_area_hashmap;

void initJVM(char* bytecode_path){
    struct Context *context = prepareJVMInit();

    /*int class_loader_method_area_entry = prepareApplicationClassLoader(context);
    int classLoaderMethodArea = get(method_area_hashmap, "java/lang/ClassLoader");*/

    FILE *bytecode_file = fopen(bytecode_path, "rb");
    int method_area = loadClass(bytecode_file, context);

    initFirstFrame(method_area, context);
}