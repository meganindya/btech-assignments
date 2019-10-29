package programs.q10.external;

import java.util.*;


public class Body {

    private Boolean skyroofPresent;
    private Boolean isConvertible;


    public void isSkyroofPresent(boolean skyroofPresent) {
        this.skyroofPresent = Boolean.valueOf(skyroofPresent);
    }

    public void isConvertible(boolean isConvertible) {
        this.isConvertible = Boolean.valueOf(isConvertible);
    }


    public HashMap<String, Object> getProperties() {
        HashMap<String, Object> properties = new HashMap<>();

        properties.put("Skyroof",           (Object) (Objects.isNull(skyroofPresent) ? "" : (skyroofPresent ? "Yes" : "No")));
        properties.put("Convertible",       (Object) (Objects.isNull(isConvertible) ? "" : (isConvertible ? "Yes" : "No")));

        return properties;
    }

}
