#include <SFML/Graphics.hpp>
#include <iostream>


const float gravityConstant = 0.001f;
const int windowWidth{ 1280 };
const int windowLength{ 800 };




class particle {

    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::CircleShape p;
    float mass;
    int r;
    int g;
    int b;
public:

    particle(int pos_x, int pos_y, float velocity_x, float velocity_y,float mass,float radius, int r, int g, int b) {
        position.x = pos_x;
        position.y = pos_y;
        velocity.x = velocity_x;
        velocity.y = velocity_y;
        this->mass = mass;
        p.setPosition(position);
        p.setRadius(radius);
        this->r = r;
        this->g = g;
        this->b = b;
    }

    particle(int pos_x, int pos_y, float velocity_x, float velocity_y, float mass, float radius) {
        position.x = pos_x;
        position.y = pos_y;
        velocity.x = velocity_x;
        velocity.y = velocity_y;
        this->mass = mass;
        p.setPosition(position);
        p.setRadius(radius);
        r = 255;
        g = 255;
        b = 255;
            

        
    }


    void draw_shape(sf::RenderWindow* window) {
        p.setFillColor(sf::Color(r, g, b));
        window->draw(p);
    }
    sf::Vector2f get_pos() {
        return position;
    }
    sf::Vector2f get_velocity() {
        return velocity;
    }

    void accelerate(sf::Vector2f acceleration) {
        velocity.x += acceleration.x;
        velocity.y += acceleration.y;
       //std::cout << velocity.x<< "\n";
    }
    void update_pos() {
        position.x += velocity.x;
        position.y += velocity.y;
        p.setPosition(position);
    }
    float get_mass() {
        return mass;
    }

    

    
    
};



sf::Vector2f find_distance(particle one, particle two) {
    sf::Vector2f distance;
    distance.x = two.get_pos().x - one.get_pos().x;
    distance.y = two.get_pos().y - one.get_pos().y;

    return distance;
}




void updatePhysics(std::vector<particle>& particles) {

    for (int i = 0; i < particles.size();i++) {
        for (int ii = 0;ii < particles.size();ii++) {

            if (!(i == ii)) {

                sf::Vector2f distance = find_distance(particles[i], particles[ii]);
                float distanceVector = sqrt(distance.x * distance.x + distance.y * distance.y);
                //std::cout << distanceVector << "\n";

                sf::Vector2f direction;
                direction.x = distance.x / distanceVector;

                //std::cout << direction.x << "\n";
                direction.y = distance.y / distanceVector;
               
                float minimumDistance = 1.0f; 
                if (distanceVector < minimumDistance) {
                    distanceVector = minimumDistance;
                }
                
                float gravitaionalForce = gravityConstant * ((particles[ii].get_mass() * particles[i].get_mass()) / (distanceVector * distanceVector));
               
                float accelerationVector = gravitaionalForce / particles[i].get_mass();
                //std::cout << accelerationVector << "\n";
                sf::Vector2f acceleration;
                acceleration.x = accelerationVector * direction.x;
                acceleration.y = accelerationVector * direction.y;
                particles[i].accelerate(acceleration);
                

            }
        }
    }

}




//vector for adding, removing, or editing particles
std::vector<particle> particles{
    particle(800.0f, 360.0f, .00, .00, 52000.0f, 12,255,255,0), 
    particle(700.0f, 280.0f, 0.5f, -.5f,5.f, 4, 51, 153, 255),
    particle(845.0f, 395.0f, -.75f, .3f,6.f, 4, 255, 0, 0), 
    particle(760.0f, 160.0f, .54f, 0.f,5.f, 4, 166, 225, 121),
    particle(800.0f, 460.0f, -.7f, 0.f,5.f, 4, 51, 0, 0),
    particle(760.0f, 130.0f, .5f, 0.f,6.f, 4, 153, 76, 0),
};




int main()
{
    


    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ windowWidth,windowLength }), "Gravity Simulation");
    window->setFramerateLimit(120);

   



    while (window->isOpen()) {
        while(const std::optional event = window ->pollEvent())
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }
        
        
        
        updatePhysics(particles);
        for (int i = 0; i < particles.size();i++) {
            particles[i].update_pos();
        }
        
        //render
        window->clear(sf::Color(71, 60, 60));
        //for black background
        //window->clear(sf::Color(0, 0, 0));

        for (int i = 0; i < particles.size(); i++) {
            particles[i].draw_shape(window);
        }

        window->display();
        }
    delete window;
    return 0;
}
    

   

    