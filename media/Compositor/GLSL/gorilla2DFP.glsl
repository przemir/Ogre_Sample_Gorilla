#version ogre_glsl_ver_330

vulkan_layout( ogre_s0 ) uniform sampler2D atlas;

/*
vulkan_layout( location = 0 ) in vec4 oUv;
vulkan_layout( location = 1 ) in vec4 oColor;
*/

vulkan_layout( location = 0 )
in block
{
    vec4 oUv;
    vec4 oColor;
} inPs;

vulkan_layout( location = 0 )
out vec4 fragColour;

void main()
{
    fragColour = texture(atlas, inPs.oUv.xy) * inPs.oColor;
}
