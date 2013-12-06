/**
 * service.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Implements a shuttle service.
 */

// default height
var HEIGHT = 0.8;

// default latitude
var LATITUDE = 42.3745615030193;

// default longitude
var LONGITUDE = -71.11803936751632;

// default heading
var HEADING = 1.757197490907891;

// default number of seats
var SEATS = 10;

// default velocity
var VELOCITY = 50;

// global reference to shuttle's marker on 2D map
var bus = null;

// global reference to 3D Earth
var earth = null;

// global reference to 2D map
var map = null;

// global reference to shuttle
var shuttle = null;

// keep track of points
var points = 0;  

// object of colors
var COLORS = 
{
    "Adams House": {color: "adams"},
    "Cabot House": {color: "cabot"},
    "Currier House": {color: "currier"},
    "Dunster House": {color: "dunster"},
    "Eliot House": {color: "eliot"},
    "Kirkland House": {color: "kirkland"},
    "Leverett House": {color: "leverett"},
    "Lowell House": {color: "lowell"},
    "Mather House": {color: "mather"},
    "Pforzheimer House": {color: "pforzheimer"},
    "Quincy House": {color: "quincy"},
    "Winthrop House": {color: "winthrop"}
};

// load version 1 of the Google Earth API
google.load("earth", "1");

// load version 3 of the Google Maps API
google.load("maps", "3", {other_params: "sensor=false"});

// once the window has loaded
$(window).load(function() {

    // listen for keydown anywhere in body
    $(document.body).keydown(function(event) {
        return keystroke(event, true);
    });

    // listen for keyup anywhere in body
    $(document.body).keyup(function(event) {
        return keystroke(event, false);
    });

    // listen for click on Drop Off button
    $("#dropoff").click(function(event) {
        dropoff();
    });

    // listen for click on Pick Up button
    $("#pickup").click(function(event) {
        pickup();
    });

    // load application
    load();
});

// unload application
$(window).unload(function() {
    unload();
});

/**
 * Renders seating chart.
 */
function chart()
{
    var html = "<ol start='0'>";
    for (var i = 0; i < shuttle.seats.length; i++) 
    {
        if (shuttle.seats[i] == null)
        {
            html += "<li>Empty Seat</li>";
        }
        else
        {
            // changes color according to house
            html += "<li class="+ COLORS[shuttle.seats[i].house].color + ">" 
            + shuttle.seats[i].name + ", " + shuttle.seats[i].house + "</li>";
        }
    }
    html += "</ol>";
    $("#chart").html(html);
}

/**
 * Drops up passengers if their stop is nearby.
 */
function dropoff()
{
    // initializes drop check to 0
    var drop = 0; 
    
    // iterate through passengers
    for (var i in shuttle.seats)
    {
        // skip any seats that have no one in them
        if(shuttle.seats[i] != null)
        {
            
            // finds latitude of house
            lathouse = HOUSES[shuttle.seats[i].house].lat;
            
            // finds longitude of house
            lnghouse = HOUSES[shuttle.seats[i].house].lng;
               
            // find shuttle distance from house
            var housedist = shuttle.distance(lathouse, lnghouse);
            
            // occurs only if distance is less than 30 m
            if (housedist < 30)
            {
                // set seat to null
                shuttle.seats[i] = null; 
                
                // refresh list of seats
                chart();
                
                // indicate that a drop has happened
                drop = 1; 
                
                // increase points
                points++; 
                
                // announce points
                $("#announcements").html("points: " + points);
            }
        }
    }
    
    // make announcement if drop has not happened
    if (drop == 0)
    { 
        $("#announcements").html("House is too far!");
    }
}
/**
 * Called if Google Earth fails to load.
 */
function failureCB(errorCode) 
{
    // report error unless plugin simply isn't installed
    if (errorCode != ERR_CREATE_PLUGIN)
    {
        alert(errorCode);
    }
}

/**
 * Handler for Earth's frameend event.
 */
function frameend() 
{
    shuttle.update();
}

/**
 * Called once Google Earth has loaded.
 */
function initCB(instance) 
{
    // retain reference to GEPlugin instance
    earth = instance;

    // specify the speed at which the camera moves
    earth.getOptions().setFlyToSpeed(100);

    // show buildings
    earth.getLayerRoot().enableLayerById(earth.LAYER_BUILDINGS, true);

    // disable terrain (so that Earth is flat)
    earth.getLayerRoot().enableLayerById(earth.LAYER_TERRAIN, false);

    // prevent mouse navigation in the plugin
    earth.getOptions().setMouseNavigationEnabled(false);

    // instantiate shuttle
    shuttle = new Shuttle({
        heading: HEADING,
        height: HEIGHT,
        latitude: LATITUDE,
        longitude: LONGITUDE,
        planet: earth,
        seats: SEATS,
        velocity: VELOCITY
    });

    // synchronize camera with Earth
    google.earth.addEventListener(earth, "frameend", frameend);

    // synchronize map with Earth
    google.earth.addEventListener(earth.getView(), "viewchange", viewchange);

    // update shuttle's camera
    shuttle.updateCamera();

    // show Earth
    earth.getWindow().setVisibility(true);

    // render seating chart
    chart();

    // populate Earth with passengers and houses
    populate();
}

/**
 * Handles keystrokes.
 */
function keystroke(event, state)
{
    // ensure we have event
    if (!event)
    {
        event = window.event;
    }

    // left arrow
    if (event.keyCode == 37)
    {
        shuttle.states.turningLeftward = state;
        $("#announcements").html("no announcements at this time");
        return false;
    }

    // up arrow
    else if (event.keyCode == 38)
    {
        shuttle.states.tiltingUpward = state;
        $("#announcements").html("no announcements at this time");
        return false;
    }

    // right arrow
    else if (event.keyCode == 39)
    {
        shuttle.states.turningRightward = state;
        $("#announcements").html("no announcements at this time");
        return false;
    }

    // down arrow
    else if (event.keyCode == 40)
    {
        shuttle.states.tiltingDownward = state;
        $("#announcements").html("no announcements at this time");
        return false;
    }

    // A, a
    else if (event.keyCode == 65 || event.keyCode == 97)
    {
        shuttle.states.slidingLeftward = state;
        $("#announcements").html("no announcements at this time");
        return false;
    }

    // D, d
    else if (event.keyCode == 68 || event.keyCode == 100)
    {
        shuttle.states.slidingRightward = state;
        $("#announcements").html("no announcements at this time");
        return false;
    }
  
    // S, s
    else if (event.keyCode == 83 || event.keyCode == 115)
    {
        shuttle.states.movingBackward = state;  
        $("#announcements").html("no announcements at this time");   
        return false;
    }

    // W, w
    else if (event.keyCode == 87 || event.keyCode == 119)
    {
        shuttle.states.movingForward = state;
        $("#announcements").html("no announcements at this time");    
        return false;
    }
    // increase velocity X, x
    else if (event.keyCode == 88 || event.keyCode == 120)
    {
        shuttle.velocity = shuttle.velocity + 2;   
        $("#announcements").html("Current velocity is " + shuttle.velocity);   
        return false;
    }

    // decrease velocity Z, z
    else if (event.keyCode == 90 || event.keyCode == 122)
    {
        shuttle.velocity = shuttle.velocity - 2; 
        $("#announcements").html("Current velocity is " + shuttle.velocity);    
        return false;
    }
  
    return true;
}

/**
 * Loads application.
 */
function load()
{
    // embed 2D map in DOM
    var latlng = new google.maps.LatLng(LATITUDE, LONGITUDE);
    map = new google.maps.Map($("#map").get(0), {
        center: latlng,
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        scrollwheel: false,
        zoom: 17,
        zoomControl: true
    });

    // prepare shuttle's icon for map
    bus = new google.maps.Marker({
        icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/bus.png",
        map: map,
        title: "you are here"
    });

    // embed 3D Earth in DOM
    google.earth.createInstance("earth", initCB, failureCB);
}

/**
 * Picks up nearby passengers.
 */
function pickup()
{ 
    // check if too far
    check = 0;
    
    // iterate through passengers
    for (var i in PASSENGERS)
    {
        // enter if placemark is not null
        if (PASSENGERS[i].placemark != null)
        {
            // finds latitude
            lat = PASSENGERS[i].placemark.getGeometry().getLatitude();
        
            // finds longitutde
            lng = PASSENGERS[i].placemark.getGeometry().getLongitude();
            
            // find distance from shuttle
            var dist = shuttle.distance(lat, lng);
            
            // occurs only if distance is less than 15 m
            if (dist < 15)
            {
                // indicates that a passenger has been picked up
                check = 1;  
                
                // check if passengers are freshmen
                if (PASSENGERS[i].house in HOUSES == false)
                {
                    $("#announcements").html("Sorry, we don't pick up freshmen!");
                    break;
                }
                
                // iterates over shuttle seats
                for (var j = 0; j < shuttle.seats.length; j++)
                {
                    // start by assuming seats are full
                    full = 1
                    
                    // enter if empty seat                 
                    if (shuttle.seats[j] == null)
                    {
                        // assume empty seat
                        full = 0
                        
                        // put passenger into empty seat
                        shuttle.seats[j] = PASSENGERS[i];
                        
                        // refresh list of seats
                        chart();
                        
                        // removes passenger from placemark
                        var features = earth.getFeatures();
                        features.removeChild(PASSENGERS[i].placemark);
                        PASSENGERS[i].placemark = null;
                        
                        // removes passenger from marker
                        PASSENGERS[i].marker.setMap(null);
                        PASSENGERS[i].marker = null;
                        
                        // announce points
                        $("#announcements").html("points: " + points);
                        break;
                    }
                }
                
                // enter if seats are full
                if (full == 1)
                {
                    $("#announcements").html("Sorry, there is no room on the bus!");
                }
            }
        }
    }
    
    // enter if shuttle is too far
    if (check == 0)
    {
        $("#announcements").html("Shuttle is too far!");
    }
}

/**
 * Populates Earth with passengers and houses.
 */
function populate()
{
    // mark houses
    for (var house in HOUSES)
    {
        // plant house on map
        new google.maps.Marker({
            icon: "https://google-maps-icons.googlecode.com/files/home.png",
            map: map,
            position: new google.maps.LatLng(HOUSES[house].lat, HOUSES[house].lng),
            title: house
        });
    }

    // get current URL, sans any filename
    var url = window.location.href.substring(0, (window.location.href.lastIndexOf("/")) + 1);

    // scatter passengers
    for (var i = 0; i < PASSENGERS.length; i++)
    {
        // pick a random building
        var building = BUILDINGS[Math.floor(Math.random() * BUILDINGS.length)];

        // prepare placemark
        var placemark = earth.createPlacemark("");
        placemark.setName(PASSENGERS[i].name + " to " + PASSENGERS[i].house);

        // prepare icon
        var icon = earth.createIcon("");
        icon.setHref(url + "/img/" + PASSENGERS[i].username + ".jpg");

        // prepare style
        var style = earth.createStyle("");
        style.getIconStyle().setIcon(icon);
        style.getIconStyle().setScale(4.0);

        // prepare stylemap
        var styleMap = earth.createStyleMap("");
        styleMap.setNormalStyle(style);
        styleMap.setHighlightStyle(style);

        // associate stylemap with placemark
        placemark.setStyleSelector(styleMap);

        // prepare point
        var point = earth.createPoint("");
        point.setAltitudeMode(earth.ALTITUDE_RELATIVE_TO_GROUND);
        point.setLatitude(building.lat);
        point.setLongitude(building.lng);
        point.setAltitude(0.0);

        // associate placemark with point
        placemark.setGeometry(point);

        // add placemark to Earth
        earth.getFeatures().appendChild(placemark);

        // add marker to map
        var marker = new google.maps.Marker({
            icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/man.png",
            map: map,
            position: new google.maps.LatLng(building.lat, building.lng),
            title: PASSENGERS[i].name + " at " + building.name
        });
        
        // adds marker and placemarker objects to passenger global array
        PASSENGERS[i].marker = marker;
        PASSENGERS[i].placemark = placemark;
    }
}

/**
 * Handler for Earth's viewchange event.
 */
function viewchange() 
{
    // keep map centered on shuttle's marker
    var latlng = new google.maps.LatLng(shuttle.position.latitude, shuttle.position.longitude);
    map.setCenter(latlng);
    bus.setPosition(latlng);
}

/**
 * Unloads Earth.
 */
function unload()
{
    google.earth.removeEventListener(earth.getView(), "viewchange", viewchange);
    google.earth.removeEventListener(earth, "frameend", frameend);
}
