#version ogre_glsl_ver_330

vulkan_layout( OGRE_DIFFUSE ) in vec4 colour;
vulkan_layout( OGRE_POSITION ) in vec3 vertex;
vulkan_layout( OGRE_TEXCOORD0 ) in vec2 uv0;

out gl_PerVertex
{
    vec4 gl_Position;
};

/*
vulkan_layout( location = 0 ) out vec4 oUv;
vulkan_layout( location = 1 ) out vec4 oColor;
*/

vulkan_layout( location = 0 )
out block
{
    vec4 oUv;
    vec4 oColor;
} outVs;

void main()
{
    outVs.oUv = vec4(uv0, 1.0, 1.0);
    outVs.oColor = colour;
    gl_Position = vec4(vertex, 1.0);
}
