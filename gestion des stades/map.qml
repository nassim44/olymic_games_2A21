import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6
import Location 1.0
Rectangle {
    width: 1700
    height: 850
    visible: true
    Plugin {
        id: mapPlugin
        name: "osm" // "mapboxgl", "esri", ...
        PluginParameter {
                   name: "osm.mapping.providersrepository.disabled"
                   value: "true"
               }
               PluginParameter {
                   name: "osm.mapping.providersrepository.address"
                   value: "http://maps-redirect.qt.io/osm/5.6/"
               }
    }
//36.839448552924246


    Map {
        anchors.fill: parent
        plugin: mapPlugin

        property double cordx: 36.839448552924246
        //property double cordx: Location.location
        property double cordy: 10.300041682114815
        center: QtPositioning.coordinate(cordx, cordy) // Oslo
        zoomLevel: 14
        MapQuickItem {
            coordinate: QtPositioning.coordinate(36.839448552924246, 10.300041682114815)
            sourceItem: Image {
                id: image
                source: "marker.png"
            }
            anchorPoint.x: image.width /2
            anchorPoint.y: image.height
        }
    }
}
