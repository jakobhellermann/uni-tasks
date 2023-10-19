function addSkybox() {
    const skybox = BABYLON.MeshBuilder.CreateBox("skyBox", { size: 1000.0 }, scene);
    const skyboxMaterial = new BABYLON.StandardMaterial("skyBox", scene);
    skyboxMaterial.backFaceCulling = false;
    skyboxMaterial.reflectionTexture = new BABYLON.CubeTexture("assets/skybox/skybox", scene);
    skyboxMaterial.reflectionTexture.coordinatesMode = BABYLON.Texture.SKYBOX_MODE;
    skyboxMaterial.diffuseColor = new BABYLON.Color3(0, 0, 0);
    skyboxMaterial.specularColor = new BABYLON.Color3(0, 0, 0);
    skybox.material = skyboxMaterial;
}

function addCoordinateAxis() {
    // Show coordinate system, BabylonJS uses left-handed coordinates!
    // x-axis: red, y-axis: yellow, z-axis: green
    var cylinder1 = BABYLON.Mesh.CreateCylinder("cylinder1", 0.2, 0.01, 0.01, 4, scene);
    var cylinder2 = BABYLON.Mesh.CreateCylinder("cylinder2", 0.2, 0.01, 0.01, 4, scene, false);
    var cylinder3 = BABYLON.Mesh.CreateCylinder("cylinder3", 0.2, 0.01, 0.01, 4, scene, false);
    var cmat1 = new BABYLON.StandardMaterial("cmat1", scene);
    var cmat2 = new BABYLON.StandardMaterial("cmat2", scene);
    var cmat3 = new BABYLON.StandardMaterial("cmat3", scene);
    cmat1.emissiveColor = new BABYLON.Color3(1, 0, 0); // red
    cmat2.emissiveColor = new BABYLON.Color3(1, 1, 0); // yellow
    cmat3.emissiveColor = new BABYLON.Color3(0, 1, 0); // green
    cylinder1.material = cmat1;
    cylinder2.material = cmat2;
    cylinder3.material = cmat3;
    cylinder1.position.x = 0.1;
    cylinder1.rotation.z = 0.5 * Math.PI;
    cylinder2.position.y = 0.1;
    cylinder2.rotation.z = 0.0;
    cylinder3.position.z = 0.1;
    cylinder3.rotation.x = 0.5 * Math.PI;
}

function createMaterial(name, texture, specular, emissive) {
    let material = new BABYLON.StandardMaterial(name, scene);
    material.diffuseTexture = new BABYLON.Texture(texture, scene);
    material.specularColor = specular;
    material.emissiveColor = emissive;
    material.diffuseTexture.vScale = -1;
    material.diffuseTexture.uScale = -1;
    return material;
}

function createBody(name, diameter, material) {
    let segments = 10;
    let body = BABYLON.Mesh.CreateSphere(name, segments, diameter, scene);
    body.material = material;
    return body;
}


