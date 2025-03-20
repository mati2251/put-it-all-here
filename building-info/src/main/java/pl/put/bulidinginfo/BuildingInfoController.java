package pl.put.bulidinginfo;

import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.CrossOrigin;

import pl.put.bulidinginfo.models.Location;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.List;


/**
 * This class is the controller for handling building information requests.
 */
@RestController
public class BuildingInfoController {

    private static final Logger logger = LoggerFactory.getLogger(BuildingInfoController.class);

    /**
     * This method returns the area of the location.
     * @param body - location
     * @return area of the location (unit: m^2)
     */
    @CrossOrigin
    @PostMapping("/area")
    public Float getArea(@RequestBody Location body){
        logger.info("For location: " + body.name + " area is: " + body.getArea().toString() + " m^2");
        return body.getArea();
    }

    /**
     * This method returns the cube of the location.
     * @param body - location
     * @return cube of the location (unit: m^3)
     */
    @CrossOrigin
    @PostMapping("/cube")
    public Float getCube(@RequestBody Location body){
        logger.info("For location: " + body.name + " cube is: " + body.getCube().toString() + " m^3");
        return body.getCube();
    }

    /**
     * This method returns the heating per cube meter of the location.
     * @param body - location
     * @return heating of the location (unit: W/m^3)
     */
    @CrossOrigin
    @PostMapping("/heating-per-cube-meter")
    public List<Location> getLocationsWithHigherHeatingRate(@RequestBody Location body, @RequestParam Float thresholdRate){
        logger.info("List of locations that have higher rate: " + body.getLocationsWithHigherHeatingRate(thresholdRate).toString());
        return body.getLocationsWithHigherHeatingRate(thresholdRate);
    }

    /**
     * This method returns the heating of the location.
     * @param body - location
     * @return heating of the location (unit: W)
     */
    @CrossOrigin
    @PostMapping("/heating-consumption")
    public Float getHeatingPerCube(@RequestBody Location body){
        logger.info("For location: " + body.name  + " heating consumption is: " + body.getHeatingPerCubeMeter().toString() + " W/m^3");
        return body.getHeatingPerCubeMeter();
    }

    /**
     * This method returns the lighting of the location.
     * @param body - location
     * @return lighting of the location (unit: lx)
     */
    @CrossOrigin
    @PostMapping("/lighting-power")
    public Float getLightingPower(@RequestBody Location body){
        logger.info("For location: " + body.name  + " lighting power is: " + body.getLightingPower().toString() + " W/m^2");
        return body.getLightingPower();
    }
}