vec3 blinnphong(){
    // Diffuse shading
    float diffuseIntensity = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = lightColor * objectColor * diffuseIntensity;

    // Specular shading
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularIntensity = pow(max(dot(viewDirection, reflectionDirection), 0.0), shininess);
    vec3 specular = lightColor * specularStrength * specularIntensity;

    // Ambient shading
    vec3 ambient = lightColor * objectColor * ambientStrength;

    // Final color
    return ambient + diffuse;//+ specular;
}