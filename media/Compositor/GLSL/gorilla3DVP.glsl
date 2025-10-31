#version ogre_glsl_ver_330

vulkan_layout( OGRE_POSITION ) in vec4 vertex;
vulkan_layout( OGRE_DIFFUSE ) in vec4 colour;
vulkan_layout( OGRE_TEXCOORD0 ) in vec4 uv0;

vulkan( layout( ogre_P0 ) uniform Params { )
    uniform mat4 worldViewProj;
vulkan( }; )

out gl_PerVertex
{
    vec4 gl_Position;
};

vulkan_layout( location = 0 ) out vec4 oUv;
vulkan_layout( location = 1 ) out vec4 oColor;

/*
vulkan_layout( location = 0 )
out block
{
	vec4 oUv;
  vec4 oColor;
} outVs;
*/

void main()
{
    oUv = uv0;
    oColor = colour;
    gl_Position = worldViewProj * vertex;
}
