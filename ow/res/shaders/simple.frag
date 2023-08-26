#version 450
 
in vec3 fragPosition;
in vec3 fragNormal;


uniform mat4 viewMatrix;

uniform vec3 albedo;
uniform float roughness;
uniform float metallic;
uniform vec3 emission;

uniform vec3 cameraPosition;

uniform float exposure;

out vec4 fragColor;

vec3 pbr(vec3 N, vec3 V, vec3 albedo, float roughness, float metallic, vec3 WorldPos, vec3 lightPosition, vec3 lightColor);

vec3 ACESFilmic(vec3 x)
{
    const float a = 2.51;
  const float b = 0.03;
  const float c = 2.43;
  const float d = 0.59;
  const float e = 0.14;
  return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}

void main()
{
    vec3 viewPosition = cameraPosition;

    //8152.711959882338
    vec3 lightColor = vec3(8152.711959882338, 8152.711959882338, 8152.711959882338);
    //vec3 lightColor = vec3(150.0, 150.0, 150.0);
    vec3 lightPosition = vec3(5.0, 5.0, 0.0);

    vec3 N = normalize(fragNormal);
    vec3 lightDirection = normalize(lightPosition - fragPosition);
    vec3 V = normalize(viewPosition - fragPosition);

    vec3 radiance = pbr(N, V, albedo, roughness, metallic, fragPosition, lightPosition, lightColor);
    radiance += emission;

    radiance *= pow(2.0, exposure);

    /* Tone mapping */
    //vec3 color = radiance / (radiance + vec3(1.0));
    vec3 color = ACESFilmic(radiance);

    /* Gamma correction */
    color = pow(color, vec3(1.0/2.2));  

    fragColor = vec4(color, 1.0);
}