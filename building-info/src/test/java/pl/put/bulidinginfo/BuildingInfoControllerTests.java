package pl.put.bulidinginfo;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import pl.put.bulidinginfo.models.Room;
import pl.put.bulidinginfo.models.RoomCompound;
import pl.put.bulidinginfo.models.Type;

import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;

@SpringBootTest
public class BuildingInfoControllerTests {

    @Autowired
    private BuildingInfoController buildingInfoController;

    @Test
    public void contextLoads() {
    }

    @Test
    public void testGetBuildingInfo() {
        Room room = new Room(1, "Room", 10.0f, 0.0f, 0.0f, 0);
        Room room2 = new Room(2, "Room2", 20.0f, 0.0f, 0.0f, 0);
        RoomCompound floor = new RoomCompound(3, "Floor", Type.FLOOR, List.of(room, room2));
        Room room3 = new Room(4, "Room3", 30.0f, 0.0f, 0.0f, 0);
        Room room4 = new Room(5, "Room4", 40.0f, 0.0f, 0.0f, 0);
        RoomCompound floor2 = new RoomCompound(6, "Floor2", Type.FLOOR, List.of(room3, room4));
        RoomCompound building = new RoomCompound(7, "Building", Type.BUILDING, List.of(floor, floor2));
        assertEquals(buildingInfoController.getArea(building), 100.0f);
    }

    @Test
    public void testOfCallsGetArea(){
        Room building = mock(Room.class);
        buildingInfoController.getArea(building);
        verify(building, times(2)).getArea();
    }

    @Test
    public void testGetCube() {
        Room room = new Room(1, "Room", 10.0f, 30.0f, 0.0f, 0);
        Room room2 = new Room(2, "Room2", 20.0f, 40.0f, 0.0f, 0);
        RoomCompound floor = new RoomCompound(3, "Floor", Type.FLOOR, List.of(room, room2));
        Room room3 = new Room(4, "Room3", 30.0f, 50.0f, 0.0f, 0);
        Room room4 = new Room(5, "Room4", 40.0f, 20.0f, 0.0f, 0);
        RoomCompound floor2 = new RoomCompound(6, "Floor2", Type.FLOOR, List.of(room3, room4));
        RoomCompound building = new RoomCompound(7, "Building", Type.BUILDING, List.of(floor, floor2));
        assertEquals(buildingInfoController.getCube(building), 140.0f);
    }

    @Test
    public void testOfCallsGetCube(){
        Room building = mock(Room.class);
        buildingInfoController.getCube(building);
        verify(building, times(2)).getCube();
    }

    @Test
    public void getLocationsWithHigherHeatingRate() {
        Room room = new Room(1, "Room", 10.0f, 30.0f, 31.0f, 0);
        Room room2 = new Room(2, "Room2", 20.0f, 40.0f, 30.0f, 0);
        RoomCompound floor = new RoomCompound(3, "Floor", Type.FLOOR, List.of(room, room2));
        Room room3 = new Room(4, "Room3", 30.0f, 50.0f, 60.0f, 0);
        Room room4 = new Room(5, "Room4", 40.0f, 20.0f, 60.0f, 0);
        RoomCompound floor2 = new RoomCompound(6, "Floor2", Type.FLOOR, List.of(room3, room4));
        RoomCompound building = new RoomCompound(7, "Building", Type.BUILDING, List.of(floor, floor2));

        assertEquals(buildingInfoController.getLocationsWithHigherHeatingRate(building, 1.0f), List.of(room, room3, room4));
    }

    @Test
    public void testOfCallsGetLocationsWithHigherHeatingRateForBuilding(){
        Room building = mock(Room.class);
        buildingInfoController.getLocationsWithHigherHeatingRate(building, 1.0f);
        verify(building, times(2)).getLocationsWithHigherHeatingRate(1.0f);
    }

    @Test
    public void getHeatingPerCube() {
        Room room = new Room(1, "Room", 10.0f, 30.0f, 25.0f, 0);
        Room room2 = new Room(2, "Room2", 20.0f, 40.0f, 30.0f, 0);
        RoomCompound floor = new RoomCompound(3, "Floor", Type.FLOOR, List.of(room, room2));
        Room room3 = new Room(4, "Room3", 30.0f, 50.0f, 60.0f, 0);
        Room room4 = new Room(5, "Room4", 40.0f, 20.0f, 60.0f, 0);
        RoomCompound floor2 = new RoomCompound(6, "Floor2", Type.FLOOR, List.of(room3, room4));
        RoomCompound building = new RoomCompound(7, "Building", Type.BUILDING, List.of(floor, floor2));

        assertEquals(buildingInfoController.getHeatingPerCube(building), 1.25f);
    }

    @Test
    public void testOfCallsGetHeatingPerCubeMeter(){
        Room building = mock(Room.class);
        buildingInfoController.getHeatingPerCube(building);
        verify(building, times(2)).getHeatingPerCubeMeter();
    }

    @Test
    public void getLightingPower() {
        Room room = new Room(1, "Room", 10.0f, 30.0f, 25.0f, 150);
        Room room2 = new Room(2, "Room2", 20.0f, 40.0f, 30.0f, 250);
        RoomCompound floor = new RoomCompound(3, "Floor", Type.FLOOR, List.of(room, room2));
        Room room3 = new Room(4, "Room3", 30.0f, 50.0f, 60.0f, 150);
        Room room4 = new Room(5, "Room4", 40.0f, 20.0f, 60.0f, 300);
        RoomCompound floor2 = new RoomCompound(6, "Floor2", Type.FLOOR, List.of(room3, room4));
        RoomCompound building = new RoomCompound(7, "Building", Type.BUILDING, List.of(floor, floor2));

        assertEquals(buildingInfoController.getLightingPower(building), 8.5f);
    }

    @Test
    public void testOfCallsGetLightingPower(){
        Room building = mock(Room.class);
        buildingInfoController.getLightingPower(building);
        verify(building, times(2)).getLightingPower();
    }
}
