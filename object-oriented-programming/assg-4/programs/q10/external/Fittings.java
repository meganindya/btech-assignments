package programs.q10.external;

import java.util.*;


public class Fittings {

    private String spoilerType;
    private String bonnetMaterial;
    private String exhaustType;


    public void setSpoilerType(String spoilerType) {
        this.spoilerType = spoilerType;
    }

    public void setBonnetMaterial(String bonnetMaterial) {
        this.bonnetMaterial = bonnetMaterial;
    }

    public void setExhaustType(String exhaustType) {
        this.exhaustType = exhaustType;
    }


    public HashMap<String, Object> getProperties() {
        HashMap<String, Object> properties = new HashMap<>();

        properties.put("Spoiler Type",      (Object) spoilerType);
        properties.put("Bonnet Material",   (Object) bonnetMaterial);
        properties.put("Exhaust Type",      (Object) exhaustType);

        return properties;
    }

}
