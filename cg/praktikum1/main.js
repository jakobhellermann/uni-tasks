// Check support
if (!BABYLON.Engine.isSupported()) {
    window.alert('Browser not supported');
    throw new Error();
}

// -- PARAMETERS (frequency in per day, radius in AU) --
// simulation parameters:
let daysPerSecond = 1;
let notToScaleMoonDistance = 100;
let notToScaleMarsMoonDistance = 1500;
let notToScaleBodySize = 3000;
let notToScaleSunSize = 1 / 200;
let notToScaleMarsMoonSize = 50;

// physically based:
let distanceEarthMoon = 384_400;
let distanceSunEarth = 150_000_000;
let distanceSunMars = 228_000_000;
let distanceMarsPhobos = 9_377;
let distanceMarsDeimos = 23_460;
let sunDiameter = 1_392_700;
let earthDiameter = 12_742;
let moonDiameter = 3_474.8;
let marsDiameter = 6_779;
let phobosDiameter = 22.2;
let deimosDiameter = 12.6;

let earthConfiguration = {
    revolutionFrequency: 1 / 365.24,
    revolutionRadius: distanceSunEarth / distanceSunEarth,
    rotationFrequency: 1,
};
let moonConfiguration = {
    revolutionFrequency: 1 / 27.3,
    revolutionRadius: distanceEarthMoon / distanceSunEarth * notToScaleMoonDistance,
    rotationFrequency: 1 / 27.3, // synchronous orbit
};
let satelliteConfiguration = {
    revolutionFrequency: 3 * moonConfiguration.revolutionFrequency,
    revolutionRadius: 0.07,
    rotationFrequency: 3 * moonConfiguration.rotationFrequency,
};
let marsConfiguration = {
    revolutionFrequency: 1 / 687,
    revolutionRadius: distanceSunMars / distanceSunEarth,
    rotationFrequency: 1 / 1.616,
};
let phobosConfiguration = {
    revolutionFrequency: 24 / 7.66,
    revolutionRadius: distanceMarsPhobos / distanceSunEarth * notToScaleMarsMoonDistance,
    rotationFrequency: 24 / 7.66 // synchronous orbit
};
let deimosConfiguration = {
    revolutionFrequency: 24 / 30.31,
    revolutionRadius: distanceMarsDeimos / distanceSunEarth * notToScaleMarsMoonDistance,
    rotationFrequency: 24 / 30.31, // synchronous orbit
};

let sunRotationFrequency = 1 / 24.47;

// babylon.js setup
var canvas = document.getElementById("renderCanvas");
var engine = new BABYLON.Engine(canvas, true);
var scene = new BABYLON.Scene(engine);
var camera = new BABYLON.ArcRotateCamera("ArcRotateCamera", -Math.PI / 4.0, 0.25 * Math.PI, 4.0, new BABYLON.Vector3(0, 0, 0), scene); // Reguläre Kamera mit festem Blickpunkt
const ambientLight = new BABYLON.HemisphericLight("HemiLight", new BABYLON.Vector3(0, 1, 0), scene);
var pointLight = new BABYLON.PointLight("dir01", new BABYLON.Vector3(-0.0, -0.0, 0.0), scene);
pointLight.diffuse = new BABYLON.Color3(1.0, 1.0, 1.0);

addCoordinateAxis();
addSkybox();

let sunSize = sunDiameter / distanceSunEarth * notToScaleBodySize * notToScaleSunSize;
let earthSize = earthDiameter / distanceSunEarth * notToScaleBodySize;
let moonSize = moonDiameter / distanceSunEarth * notToScaleBodySize;
let marsSize = marsDiameter / distanceSunEarth * notToScaleBodySize;
let phobosSize = phobosDiameter / distanceSunEarth * notToScaleBodySize * notToScaleMarsMoonSize;
let deimosSize = deimosDiameter / distanceSunEarth * notToScaleBodySize * notToScaleMarsMoonSize;
let satelliteSize = 0.02;

let earth = createBody(
    "Earth",
    earthSize,
    createMaterial("default1", "assets/earth.jpg", new BABYLON.Color3(0.1, 0.1, 0.1), new BABYLON.Color3(0.2, 0.2, 0.2))
);
let moon = createBody(
    "moon",
    moonSize,
    createMaterial("default2", "assets/moon.jpg", new BABYLON.Color3(0, 0, 0), new BABYLON.Color3(0.2, 0.2, 0.2),
    )
);
let satellite = createBody(
    "satellite",
    satelliteSize,
    createMaterial("default5", "assets/metal.jpg", new BABYLON.Color3(0.2, 0.2, 0.2), new BABYLON.Color3(0.3, 0.3, 0.3),)
);
let sun = createBody(
    "Sun",
    sunSize,
    createMaterial("default3", "assets/sun.jpg", new BABYLON.Color3(0, 0, 0), new BABYLON.Color3(1, 1, 1))
);
let mars = createBody(
    "moon",
    marsSize,
    createMaterial("default4", "assets/mars.jpg", new BABYLON.Color3(0, 0, 0), new BABYLON.Color3(0.2, 0.2, 0.2),)
);
let phobos = createBody(
    "phobos",
    phobosSize,
    // http://www.celestiamotherlode.net/catalog/marsmoons.html
    createMaterial("default6", "assets/phobos.jpg", new BABYLON.Color3(0, 0, 0), new BABYLON.Color3(0.2, 0.2, 0.2),)
);
let deimos = createBody(
    "deimos",
    phobosSize,
    createMaterial("default7", "assets/deimos.jpg", new BABYLON.Color3(0, 0, 0), new BABYLON.Color3(0.2, 0.2, 0.2),)
);

var startTime = new Date().getTime();
var lastTime = startTime;

// let initialTimeOffset = Math.random() * 365;
let initialTimeOffset = 200;

function move(day, object, configuration, base = null) {
    object.position.x = configuration.revolutionRadius * Math.sin(2 * Math.PI * configuration.revolutionFrequency * day);
    object.position.z = configuration.revolutionRadius * Math.cos(2 * Math.PI * configuration.revolutionFrequency * day);
    if (base !== null) {
        object.position.x += base.position.x;
        object.position.z += base.position.z;
    }
    object.rotation.y = 2 * Math.PI * configuration.rotationFrequency * day;
}

scene.registerBeforeRender(() => {
    var time = new Date().getTime();           // get millisseconds since 1970
    var elapsed_t = time - startTime; // milliseconds since start
    var delta_t = time - lastTime;    // milliseconds since last frame
    lastTime = time;

    let realtimeSeconds = elapsed_t / 1000.0;
    let day = realtimeSeconds * daysPerSecond + initialTimeOffset;

    move(day, earth, earthConfiguration);
    move(day, moon, moonConfiguration, earth);
    move(day, satellite, satelliteConfiguration, moon);
    move(day, mars, marsConfiguration);
    move(day, phobos, phobosConfiguration, mars);
    move(day, deimos, deimosConfiguration, mars);

    sun.rotation.y = 2 * Math.PI * sunRotationFrequency * day;
});

scene.activeCamera.attachControl(canvas);
engine.runRenderLoop(() => {
    if (scene) {
        scene.render();
    }
});

// Resize
window.addEventListener("resize", function () {
    engine.resize();
});