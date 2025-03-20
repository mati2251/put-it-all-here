package pl.put.bulidinginfo.models;

import java.util.ArrayList;
import java.util.List;

/**
 * This is a class named Room that extends the abstract class Location.
 * It represents a room in a building.
 * It has several fields that represent the characteristics of the room such as area, cube, heating, and lighting.
 * It a part of the composite design pattern.
 */
public class Room extends Location {
    /**
     * Area of the room
     */
    public Float area;
    /**
     * Cube of the room
     */
    public Float cube;
    /**
     * Heating of the room
     */
    public Float heating;
    /**
     * Lighting of the room
     */
    public Integer lighting;

    /**
     * Constructor for the Room class.
     *
     * @param id       Integer representing the unique identifier for the room.
     * @param name     String representing the name of the room.
     * @param area     Float representing the area of the room.
     * @param cube     Float representing the cube of the room.
     * @param heating  Float representing the heating of the room.
     * @param lighting Integer representing the lighting of the room.
     */
    public Room(Integer id, String name, Float area, Float cube, Float heating, Integer lighting) {
        super(id, name);
        this.area = area;
        this.type = Type.ROOM;
        this.cube = cube;
        this.heating = heating;
        this.lighting = lighting;
    }

    /**
     * Method to get the area of the room.
     * @return Float representing the area of the room.
     */
    @Override
    public Float getArea() {
        return this.area;
    }

    /**
     * Method to get the cube of the room.
     * @return Float representing the cube of the room.
     */
    @Override
    public Float getCube() {
        return this.cube;
    }

    /**
     * Method to get the heating per cube meter of the room.
     * @return Float representing the heating per cube meter of the room.
     */
    @Override
    public Float getHeatingPerCubeMeter() {
        return (this.heating / this.cube);
    }

    /**
     * Method to get the heating of the room.
     * @return Float representing the heating of the room.
     */
    @Override
    public Float getHeating() {
        return this.heating;
    }

    /**
     * Method to get the lighting of the room.
     * @return int representing the lighting of the room.
     */
    @Override
    public int getLighting() {
        return this.lighting;
    }

    /**
     * Method to get the lighting power of the room.
     * @return Float representing the lighting power of the room.
     */
    @Override
    public Float getLightingPower() {
        return (this.lighting / this.area);
    }

    /**
     * Method to get the locations with a higher heating rate than a given threshold.
     * @param thresholdRate Float representing the threshold heating rate.
     * @return List of Location objects with a higher heating rate than the given threshold.
     */
    @Override
    public List<Location> getLocationsWithHigherHeatingRate(Float thresholdRate) {
        List<Location> locations = new ArrayList<>();
        if (this.getHeatingPerCubeMeter() > thresholdRate) {
            locations.add(this);
        }
        return locations;
    }
}