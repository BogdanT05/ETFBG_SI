package guns;

import characters.Character;

public abstract class Gun {
    protected int damage;
    protected double precision;
    protected Character owner;

    public Gun(int damage, double precision) {
        this.damage = damage;
        this.precision = precision;
    }

    public void effect(Character target){
        if(Math.random() < precision){
            System.out.println("Character: " + owner.getName() + " shoot at: " + target.getName() + " and dealt : " + this.damage + " damage");
            target.collision(this);
        }
    }

    public abstract String type();

    public int getDamage() {
        return damage;
    }

    public void setDamage(int damage) {
        this.damage = damage;
    }

    public double getPrecision() {
        return precision;
    }

    public void setPrecision(double precision) {
        this.precision = precision;
    }

    public Character getOwner() {
        return owner;
    }

    public void setOwner(Character owner) {
        this.owner = owner;
    }
}
