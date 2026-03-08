package guns;

public class Rifle extends Gun{

    public Rifle(){
        super(3, 0.8);
    }

    public Rifle(int damage, double precision){
        super(damage, precision);
    }
}
