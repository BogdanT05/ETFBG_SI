package guns;

import characters.Character;

public class Grenade extends Gun{

    public Grenade(int damage, double precision) {
        super(damage, precision);
    }

    public Grenade(){
        super(5, 0.7);
    }

    @Override
    public void effect(Character target){
        if(Math.random() < precision){
            System.out.println("Character: " + owner.getName() + " shoot at: " + target.getName() + " and dealt : " + this.damage + " damage");
            target.collision(this);
        }
        else{
            System.out.println("Character: " + owner.getName() + " damaged himself at dealt " + this.damage + " damage");
            owner.collision(this);
        }
    }

}
