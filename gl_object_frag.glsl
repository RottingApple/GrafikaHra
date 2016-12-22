#version 150
// A texture is expected as program attribute
uniform mat4 model;
uniform vec3 cameraPosition;

// material settings
uniform sampler2D materialTex;
uniform float materialShininess;
uniform vec3 materialSpecularColor;

uniform vec3 Lposition;
uniform vec3 Lposition2;
uniform vec3 Lintensities;
uniform float Lattenuation;
uniform float LambientCoefficient;
// The vertex shader fill feed this input
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragVert;
// Wordspace normal

// The final color
out vec4 finalColor;




// Light direction in world coordinates
vec4 lightDirection = normalize(vec4(0.0f,0.0f,-6.0f,0.0f));

void main() {
    vec3 Lpositions[2];
    Lpositions[0] = Lposition;
    Lpositions[1] = Lposition2;

    vec3 linearColor = vec3(0.0, 0.0, 0.0);
    vec4 surfaceColor = texture(materialTex, fragTexCoord);
    int numberOfLights = 2;
     for (int index = 0; index < numberOfLights; index++){
            vec3 normal = normalize(transpose(inverse(mat3(model))) * fragNormal);
            vec3 surfacePos = vec3(model * vec4(fragVert, 1));


            vec3 surfaceToLight = normalize(Lpositions[index] - surfacePos);
            vec3 surfaceToCamera = normalize(cameraPosition - surfacePos);

            //ambient
            vec3 ambient = LambientCoefficient * surfaceColor.rgb * Lintensities;

            //diffuse
            float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
            vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * Lintensities;

            //specular
            float specularCoefficient = 0.0;
            if(diffuseCoefficient > 0.0)
                specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), materialShininess);
            vec3 specular = specularCoefficient * materialSpecularColor * Lintensities;

            //attenuation
            float distanceToLight = length(Lpositions[index] - surfacePos);
            float attenuation = 1.0 / (1.0 + Lattenuation * pow(distanceToLight, 2));

            //Pre vseky svetla
            linearColor +=  ambient + attenuation*(diffuse + specular);
     }


    //final color (after gamma correction)
    vec3 gamma = vec3(1.0/2.2);
    finalColor = vec4(pow(linearColor, gamma), surfaceColor.a);

}

