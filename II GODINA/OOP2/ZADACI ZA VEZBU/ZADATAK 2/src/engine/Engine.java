package engine;
import characters.Character;
import guns.*;

public class Engine {
    static void main() {
        Character c1 = new Character("Aki", 10);
        Character c2 = new Character("Zaki", 10);
        Character c3 = new Character("Jocke", 10);

        c1.setGun(new Rifle());
        c2.setGun(new Grenade());
        c3.setGun(new Pistols());

        int round = 1;
        while(!(c1.is_defeated() && c2.is_defeated()) &&
              !(c2.is_defeated() && c3.is_defeated()) &&
              !(c3.is_defeated() && c1.is_defeated())){

            System.out.println("Round - " + round);

            if(Math.random() < 0.5){
                c1.shoot(c2);
                c1.shoot(c3);
            }

            if(Math.random() < 0.5){
                c2.shoot(c1);
                c2.shoot(c3);
            }

            if(Math.random() < 0.5){
                c3.shoot(c1);
                c3.shoot(c2);
            }

            System.out.println(c1);
            System.out.println(c2);
            System.out.println(c3);

            round++;
        }
    }
}
