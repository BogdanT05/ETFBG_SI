package characters;

import guns.Gun;

public class Character {

    private String name;
    private int health;
    private Gun gun;

    public Character(String name, int health) {
        this.name = name;
        this.health = health;
    }

    public void shoot(Character target){
        if (gun != null && !target.is_defeated() && !this.is_defeated()){
            gun.effect(target);
        }
    }

    public void collision(Gun bullet){
        reduce_health(bullet.getDamage());
    }

    public void reduce_health(int damage){
        health -= damage;

        if (health <= 0){
            health = 0;
            defeat();
        }
    }

    public void defeat(){
        System.out.println("Character: " + this.name + " is defeated");
    }

    public boolean is_defeated(){
        return health == 0;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString(){
        return "Character " + this.name + ":" + this.health;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getHealth() {
        return health;
    }

    public void setHealth(int health) {
        this.health = health;
    }

    public Gun getGun() {
        return gun;
    }

    public void setGun(Gun gun) {
        this.gun = gun;
        gun.setOwner(this);
    }
}
