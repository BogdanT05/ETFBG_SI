package colections.errors;

public class InvalidLength extends Exception{
    public InvalidLength(int length){
        super("Invalid vector length: " + length);
    }
}
