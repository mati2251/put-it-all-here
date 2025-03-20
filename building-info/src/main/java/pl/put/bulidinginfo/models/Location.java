package pl.put.bulidinginfo.models;

import com.fasterxml.jackson.annotation.JsonSubTypes;
import com.fasterxml.jackson.annotation.JsonTypeInfo;

import java.util.List;


/**
 * This is an abstract class named Location. It is used to represent a location in a building. It is base class in composite pattern.
 * It uses JsonTypeInfo and JsonSubTypes annotations to handle polymorphism during serialization and deserialization.
 * It has several abstract methods that must be implemented by any class that extends it.
 */
@JsonTypeInfo(
        use = JsonTypeInfo.Id.NAME,
        property = "type"
)
@JsonSubTypes({
        @JsonSubTypes.Type(value = Room.class, name = "ROOM"),
        @JsonSubTypes.Type(value = RoomCompound.class, name = "BUILDING"),
        @JsonSubTypes.Type(value = RoomCompound.class, name = "FLOOR")
})
public abstract class Location {
    /**
     * representing the unique identifier for the location.
     */
    public Integer id;
    /**
     * representing the name of the location.
     */
    public String name;
    /**
     * representing the type of the location.
     */
    public Type type;

    /**
     * Abstract method to get the area of the location.
     *
     * @return Float representing the area of the location.
     */
    abstract public Float getArea();

    /**
     * Abstract method to get the cube of the location.
     *
     * @return Float representing the cube of the location.
     */
    abstract public Float getCube();

    /**
     * Abstract method to get the heating of the location.
     *
     * @return Float representing the heating of the location.
     */
    abstract public Float getHeating();

    /**
     * Abstract method to get the heating per cube meter of the location.
     *
     * @return Float representing the heating per cube meter of the location.
     */
    abstract public Float getHeatingPerCubeMeter();

    /**
     * Abstract method to get the lighting of the location.
     *
     * @return int representing the lighting of the location.
     */
    abstract public int getLighting();

    /**
     * Abstract method to get the lighting power of the location.
     *
     * @return Float representing the lighting power of the location.
     */
    abstract public Float getLightingPower();

    /**
     * Abstract method to get the locations with a higher heating rate than a given threshold.
     *
     * @param thresholdRate Float representing the threshold heating rate.
     * @return List of Location objects with a higher heating rate than the given threshold.
     */
    abstract public List<Location> getLocationsWithHigherHeatingRate(Float thresholdRate);

    /**
     * Constructor for the Location class.
     *
     * @param id   Integer representing the unique identifier for the location.
     * @param name String representing the name of the location.
     */
    Location(Integer id, String name) {
        this.id = id;
        this.name = name;
    }
}