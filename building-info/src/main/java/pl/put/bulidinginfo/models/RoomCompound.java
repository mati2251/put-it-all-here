package pl.put.bulidinginfo.models;

import java.util.ArrayList;
import java.util.List;

/**
 * This is a class named RoomCompound that extends the abstract class Location.
 * It represents a compound of rooms in a building. It can be a building, a floor, or a room.
 * It also overrides the abstract methods from the Location class.
 * It a part of the composite design pattern.
 */
public class RoomCompound extends Location {

    /**
     * List of locations in the room compound
     */
    private List<Location> locations;
    /**
     * Type of the room compound (ROOM, BUILDING, FLOOR)
     */
    private Type type;

    /**
     * Constructor for the RoomCompound class.
     * @param id        Integer representing the unique identifier for the room compound.
     * @param name      String representing the name of the room compound.
     * @param type      Type representing the type of the room compound.
     * @param locations List of Location objects representing the locations in the room compound.
     */
    public RoomCompound(Integer id, String name, Type type, List<Location> locations) {
        super(id, name);
        this.locations = locations;
        this.type = type;
    }

    /**
     * Method to add a location to the room compound.
     * @param location Location object to be added to the room compound.
     */
    public void addLocation(Location location) {
        locations.add(location);
    }

    /**
     * Method to remove a location from the room compound.
     * @param location Location object to be removed from the room compound.
     */
    public void removeLocation(Location location) {
        locations.remove(location);
    }

    /**
     * Method to get the locations in the room compound.
     * @return List of Location objects representing the locations in the room compound.
     */
    public List<Location> getLocations() {
        return locations;
    }

    /**
     * Method to get the type of the room compound.
     * @return Type representing the type of the room compound.
     */
    public Type getType() {
        return this.type;
    }

    /**
     * Method to get the area of the room compound.
     * @return Float representing the area of the room compound.
     */
    @Override
    public Float getArea() {
        return this.getLocations().stream().map(Location::getArea).reduce(0f, Float::sum);
    }

    /**
     * Method to get the cube of the room compound.
     * @return Float representing the cube of the room compound.
     */
    @Override
    public Float getCube() {
        return this.getLocations().stream().map(Location::getCube).reduce(0f, Float::sum);
    }

    /**
     * Method to get the heating of the room compound.
     * @return Float representing the heating of the room compound.
     */
    @Override
    public Float getHeating() {
        return this.getLocations().stream().map(Location::getHeating).reduce(0f, Float::sum);
    }

    /**
     * Method to get the heating per cube meter of the room compound.
     * @return Float representing the heating per cube meter of the room compound.
     */
    @Override
    public Float getHeatingPerCubeMeter() {
        return (this.getHeating() / this.getCube());
    }

    /**
     * Method to get the lighting of the room compound.
     * @return int representing the lighting of the room compound.
     */
    @Override
    public int getLighting() {
        return this.getLocations().stream().map(Location::getLighting).reduce(0, Integer::sum);
    }

    /**
     * Method to get the lighting power of the room compound.
     * @return Float representing the lighting power of the room compound.
     */
    @Override
    public Float getLightingPower() {
        return (this.getLighting() / this.getArea());
    }

    /**
     * Method to get the locations with a higher heating rate than a given threshold.
     * @param thresholdRate Float representing the threshold heating rate.
     * @return List of Location objects with a higher heating rate than the given threshold.
     */
    @Override
    public List<Location> getLocationsWithHigherHeatingRate(Float thresholdRate) {
        List<Location> filteredLocations = new ArrayList<>();
        for (Location location : getLocations()) {
            filteredLocations.addAll(location.getLocationsWithHigherHeatingRate(thresholdRate));
        }
        return filteredLocations;
    }

}