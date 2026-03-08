package guns;

import characters.Character;

public class Pistols extends Gun{
    public Pistols(int damage, double precision) {
        super(damage, precision);
    }

    public Pistols(){
        super(2, 0.65);
    }

    @Override
    public void effect(Character target){
        super.effect(target);

        if(!target.is_defeated()){
            super.effect(target);
        }
    }
}
