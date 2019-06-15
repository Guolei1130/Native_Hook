#include <jni.h>
#include <string>
#include <dlfcn.h>
#include "../cpp/v_hook.h"

extern "C" int hookForPMethod();



extern "C" JNIEXPORT jstring
JNICALL
Java_com_example_vk_1hook_MainActivity_stringFromJNI(
    JNIEnv *env,
    jobject /* this */) {
  std::string hello = "Hello from C++";
  hookForPMethod();
  return env->NewStringUTF(hello.c_str());
}


class ObjPtr {
 public:
  uintptr_t reference_;
};


ObjPtr
(*sys_GetDeclaredMethodInternal)(void *self, jobject kclass, jstring name, jobjectArray args);

void *(*executableGetArtMethod)(void *ex);

ObjPtr myGetDeclaredMethodInternal(void *self, jobject kclass, jstring name, jobjectArray args) {
  ObjPtr res = sys_GetDeclaredMethodInternal(self, kclass, name, args);
  if (res.reference_ != 0) {
    void *pMethod = executableGetArtMethod((void *) (res.reference_));
    reinterpret_cast<uint32_t *>(pMethod)[1] &= 0xcfffffff;
  }
  return res;
}


extern "C" int hookForPMethod() {
  void *libc = v_dlopen("/system/lib/libart.so", RTLD_NOW);
  if (libc != NULL) {
    void *p = v_dlsym(libc, "_ZN3art6mirror5Class25GetDeclaredMethodInternalILNS_11Poin"
        "terSizeE4ELb0EEENS_6ObjPtrINS0_6MethodEEEPNS_6ThreadENS4_IS1_EENS4_INS0_6StringEEEN"
        "S4_INS0_11ObjectArrayIS1_EEEE");
    if (p != NULL) {
      v_hook_function(p,
                     reinterpret_cast<void *>(myGetDeclaredMethodInternal),
                     reinterpret_cast<void **>(&sys_GetDeclaredMethodInternal));
    }
    *(void **) (&executableGetArtMethod) =
        v_dlsym(libc, "_ZN3art6mirror10Executable12GetArtMethodEv");
    v_dlclose(libc);

  } //if

  return 1;
}

void (*setClassLoader)(void *pClass, void *new_cl);
ObjPtr (*toClass)(jclass global_jclss);

//extern "C" void makeHiddenApiAccessable(JNIEnv *env) {
//  void *libart = fake_dlopen("/system/lib/libart.so", RTLD_NOW);
//  if (libart != NULL) {
//    *(void **) (&toClass) = fake_dlsym(libart, "_ZN3art16WellKnownClasses7ToClassEP7_jclass");
//    *(void **) (&setClassLoader) =
//        fake_dlsym(libart, "_ZN3art6mirror5Class14SetClassLoaderENS_6ObjPtrINS0_11ClassLoaderEEE");
//    jclass cls = env->FindClass("com/example/support_p/ReflectionHelper");
//    ObjPtr op = toClass(cls);
//    setClassLoader((void *) op.reference_, NULL);
//  }
//}
