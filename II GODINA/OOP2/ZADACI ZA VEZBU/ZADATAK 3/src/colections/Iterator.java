package colections;

import colections.errors.OutOfBounds;

public interface Iterator {

    boolean has_elements();
    void next();
    int get_element() throws OutOfBounds;

}
