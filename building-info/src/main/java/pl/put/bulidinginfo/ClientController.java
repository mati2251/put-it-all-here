package pl.put.bulidinginfo;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;

/**
 * This class is a controller for handling gui client
 */
@Controller
public class ClientController {
    @CrossOrigin
    @GetMapping("/")
    public String index() {
        return "index";
    }
}
