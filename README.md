# Solar System

##Project Tree Folder
```
SolarSystem/
│
├── include/
│   ├── glad/
│   ├── GLFW/
│   ├── glm/
│   ├── KHR/
│   └── stb_image.h
│
├── lib/
│   └── libglfw3.a
│
├── resources/
│   ├── textures/
│   └── hdr/                
│
├── shaders/
│   ├── scene.vert
│   ├── scene.frag
│   ├── light.vert
│   ├── light.frag
│   ├── blur.vert           
│   ├── blur.frag           
│   ├── bloom_final.vert    
│   └── bloom_final.frag    
│
├── src/
│   ├── main.cpp
│   ├── glad.c
│
│   ├── core/               
│   │   ├── shader.h / shader.cpp
│   │   ├── camera.h / camera.cpp
│   │   ├── framebuffer.h / framebuffer.cpp
│
│   ├── rendering/          
│   │   ├── sphere.h / sphere.cpp
│   │   ├── renderer.h / renderer.cpp
│
│   ├── utils/              
│   │   ├── texture.h / texture.cpp
│
├── CMakeLists.txt          
└── glfw3.dll
```
