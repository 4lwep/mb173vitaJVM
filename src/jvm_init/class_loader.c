#include "class_loader.h"

int prepareApplicationClassLoader(struct Context *context){
    int class_loader_method_area_entry = loadClassLoader(context);
    executeClassLoaderClinit();

    return class_loader_method_area_entry;
}

int loadClassLoader(struct Context *context){
    //Cargar ClassLoader.class
    FILE *class_loader_file = fopen("ux0:/data/java/lang/ClassLoader.class", "rb");
    int class_loader_method_area_entry = loadClass(class_loader_file, context);

    MaHashMapEntry *class_loader_method_area_entry_data = (MaHashMapEntry*)&heap[class_loader_method_area_entry];
    MethodAreaData *class_loader_method_area_data = (MethodAreaData*)&heap[class_loader_method_area_entry_data->value];
    fprintf(log_file, "puntero a cp del class loader de rt.class -> %d\n", class_loader_method_area_data->constant_pool_ptr);

    executeClassLoaderClinit();

    return class_loader_method_area_entry;
}

void executeClassLoaderClinit(){
    //TODO
}