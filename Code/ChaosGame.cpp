#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
using namespace std;

/*

//Now a Cool Project!!!

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Sierpinski Triangle!!", Style::Default);

    vector<Vector2f> vertices;   ///push_back stuff into us!
	vector<Vector2f> points;


	Vector2f clicked;

    //Adding the font we will use
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    //Configuring the instruction text
    Text instruction_text;
    instruction_text.setFont(font);
    instruction_text.setString("LEFT CLICK to place vertices\nRIGHT CLICK to begin generating points");
    instruction_text.setCharacterSize(50);
    instruction_text.setFillColor(Color::White);

    //Configuring the point counter text
    Text point_count_text;
    point_count_text.setFont(font);
    point_count_text.setString("Points = 0");
    point_count_text.setCharacterSize(75);
    point_count_text.setFillColor(Color::Green);

    //Positioning the instruction text
    FloatRect textRect = instruction_text.getLocalBounds();
    instruction_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    instruction_text.setPosition(1920/2.0f, 1080/2.0f);

    //Positioning the point counter text
    point_count_text.setPosition(30, 30);

    //Game Loop
    while (window.isOpen())
	{

        //Declaring some variables outside the point generation loop
        //This is done incase we want to apply the midpoint translation at the end
        //Rather than applying it when the points are being created
        int poly_mid_x;
        int poly_mid_y;
        int false_poly_mid_x = 0;
        int false_poly_mid_y = 0;

        Event event;
        while (window.pollEvent(event))
		{
            //Closing the window
            if (event.type == sf::Event::Closed)
			{
				window.close();
			}
            //Grabbing mouse button inputs for various commands
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left && points.size() == 0)
				{
                    //outputting coordinates to the consol for debugging purposes
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    
                    //Collecting vertices input coordinates up to a certain ammount
                    if(vertices.size() < 20)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    
                    clicked.x = event.mouseButton.x;
					clicked.y = event.mouseButton.y;

				}
                //Using the right mouse button to place the first point and start the point generation
                //This allows more than 3 vertices to be set
                else if (event.mouseButton.button == sf::Mouse::Right && vertices.size() >= 3)
                {
                    //outputting coordinates to the consol for debugging purposes
                    std::cout << "the right button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    //Adding the input coordinates to the points vector so it can later be drawn
                    points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));

                    clicked.x = event.mouseButton.x;
					clicked.y = event.mouseButton.y;
                }
			}
    
		}


        //Giving an alternative way of closing the program
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}


        /*
        ****************************************
        Update the scene
        ****************************************
        */
        ///Vector2f v(2,2);
        ///RectangleShape rect(v);
        
        /*
        //Starting the program only when the player adds the first point
        if(points.size() > 0)
        {
            //Declaring necessary variables and constants for future calculations

            //Used in calculating the scale factor
            const double PI = 3.141592653589793;
            double n = vertices.size();
            double cosine_k;
            int sumtop = n/4; //Uses integer division similar to the floor function
            double sum_total = 0;
            double scale_factor;

            //Used for point generation
            int vert_select;
            int midpoint_x; //Only actually the midpoint when making a triangle
            int midpoint_y; //Only actually the midpoint when making a triangle

            //Used for weird math equation translation calculation
            int translation_x = 0;
            int translation_y = 0;
            int poly_rad = 0;

            //Used for the approximate midpoint translation calculation referenced above
            int largest_x = 0;
            int smallest_x = 0;
            int largest_y = 0;
            int smallest_y = 0;
            int false_largest_x = 0;
            int false_largest_y = 0;
            int false_smallest_x = 0;
            int false_smallest_y = 0;
            

            //Find the approximate Midpoint of the Polygon
            for (int i = 0; i < vertices.size(); i ++)
            {
                //Find the top of the polygon
                if(vertices[i].y > largest_y)
                {
                    largest_y = vertices[i].y;
                }

                //Find the bottom of the polygon
                if(vertices[i].y < smallest_y)
                {
                    smallest_y = vertices[i].y;
                }

                //Calculate the midpoint y value
                poly_mid_y = (largest_y + smallest_y)/2;

                //Find the rightmost point of the Polygon
                if(vertices[i].x > largest_x)
                {
                    largest_x = vertices[i].x;
                }
                //Find the leftmost point of the Polygon
                if(vertices[i].x < smallest_x)
                {
                    smallest_x = vertices[i].x;
                }

                //Calculate the midpoint x value
                poly_mid_x = (largest_x + smallest_x)/2;
            }

            //Summation loop to calculate the sum portion of the scale factor
            for(double k = 1; k < (sumtop + 1); k++)
            {
                cosine_k = cos((2*PI*k)/n);
                sum_total += cosine_k;
            }
            
            
            //summing the terms to calculate the scale factor r sub n
            scale_factor = 1/( 2*(1 + sum_total));

            //Calculating the approximate radius of the polygon
            for (int i = 0; i < vertices.size(); i++)
            {
                //Adding fractions of the average radius length to create an approximate radius for the polygon
                poly_rad += (sqrt(pow((poly_mid_x - vertices[i].x),2) + pow((poly_mid_y - vertices[i].y),2)))/vertices.size();
            }

            //Calculating translations for the points
            for(int i = 0; i < vertices.size(); i++)
            {
                translation_x += (1-scale_factor)*poly_rad*(cos(2*PI*i)/vertices.size());
            }
            for(int i = 0; i < vertices.size(); i++)
            {
                translation_y += (1-scale_factor)*poly_rad*(sin(2*PI*i)/vertices.size());
            }
            
            //Calculating point positions based on randomly selected vertices
            for(int i = 0; i < 40000; i++)
            {
                srand(time(0) + i);
                //calculate the midpoint of the wrongly translated polygon
                if (points.size() > 200 && points.size() < 400)
                {
                    for (int i = 20; i < points.size(); i ++)
                    {
                        //Find the top of the polygon
                        if(points[i].y > false_largest_y)
                        {
                            false_largest_y = points[i].y;
                        }

                        //Find the bottom of the polygon
                        if(points[i].y < false_smallest_y)
                        {
                            false_smallest_y = points[i].y;
                        }

                        //Calculate the midpoint y value
                        false_poly_mid_y = (false_largest_y + false_smallest_y)/2;

                        //Find the rightmost point of the Polygon
                        if(points[i].x > false_largest_x)
                        {
                            false_largest_x = points[i].x;
                        }
                        //Find the leftmost point of the Polygon
                        if(points[i].x < false_smallest_x)
                        {
                            false_smallest_x = points[i].x;
                        }

                        //Calculate the midpoint x value
                        false_poly_mid_x = (false_largest_x + false_smallest_x)/2;
                        }
                }

                //Normal point calculation
                vert_select = (rand() % vertices.size());
                midpoint_x = (vertices[vert_select].x + points[points.size()-1].x)*scale_factor;
                midpoint_y = (vertices[vert_select].y + points[points.size()-1].y)*scale_factor;

                //Special case point calculation for pentagons
                if(vertices.size() == 5)
                {
                    midpoint_x = -(vertices[vert_select].x - points[points.size()-1].x) / 8 * 3 + vertices[vert_select].x;
                    midpoint_y = -(vertices[vert_select].y - points[points.size()-1].y) / 8 * 3 + vertices[vert_select].y;
                }

                points.push_back(Vector2f(midpoint_x, midpoint_y));

                //Updating The Point Counting Text
                stringstream ss;
                ss << "Points = " << points.size();
                point_count_text.setString(ss.str());
            }
    

            ///generate point
            ///select random vertex
            ///calculate midpoint between vertex and last point in vector
            ///pushback newly generated coordinate
        }
        
        /*
        ****************************************
        Draw the scene
        ****************************************
        */
        /*
        ///loop through vectors and draw each coordinate
        // Clear everything from the last run frame
        window.clear();
        // Draw our game scene here

        //Drawing Point Counter
        window.draw(point_count_text);

        //Drawing Instruction Text
        if(vertices.size() == 0)
        {
            window.draw(instruction_text);
        }

        //Drawing vertices
        for(int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(2,2));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Red);
            window.draw(rect);
        }
        //Drawing points for shapes past the pentagon which require a unique translation
        if(vertices.size() > 5)
        {
            for(int i = 20; i < points.size(); i++)
            {
                RectangleShape rectp(Vector2f(2,2));
                rectp.setPosition(Vector2f(points[i].x + (poly_mid_x - false_poly_mid_x), points[i].y + (poly_mid_y - false_poly_mid_y)));
                rectp.setFillColor(Color::Blue);
                window.draw(rectp);
            }
        }
        //Normal drawing points for shapes of 5 sides and below
        else
        {
            for(int i = 20; i < points.size(); i++)
            {
                RectangleShape rectp(Vector2f(3,3));
                rectp.setPosition(Vector2f(points[i].x, points[i].y));
                rectp.setFillColor(Color::Blue);
                window.draw(rectp);
            }
        }
        
        
        window.display();
    }

    return 0;


}
*/

/*
***********************************************

!!!!!    OK NOW COMES THE COOL PROJECT    !!!!!

***********************************************
*/

int main()
{
    // Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Arena", Style::Default);

    //Creating Textures
    Texture background_texture;
    Texture wizard_texture;
    Texture fireball_texture;

    //Loading Graphics
    background_texture.loadFromFile("Graphics/Sprite-0002-Unfinished-Pixel-Arena-1920-1080.png");
    wizard_texture.loadFromFile("Graphics/Sprite-0003-64x-Wizard.png");
    fireball_texture.loadFromFile("Graphics/Sprite-0005-64x-Fireball.png");

    //Creating Sprites
    Sprite background_sprite;
    Sprite wizard_sprite;
    Sprite fireball_sprite;

    //Attaching Textures To Sprites
    background_sprite.setTexture(background_texture);
    wizard_sprite.setTexture(wizard_texture);
    fireball_sprite.setTexture(fireball_texture);

    //Positioning Sprites
    background_sprite.setPosition(0,0);

    //Positioning the Wizard
    FloatRect wizRect = wizard_sprite.getLocalBounds();
    wizard_sprite.setOrigin(wizRect.left + wizRect.width / 2.0f, wizRect.top + wizRect.height / 2.0f);
    bool wiz_move_up = false;
    bool wiz_move_left = false;
    bool wiz_move_right = false;
    bool wiz_move_down = false;
    float wiz_x_pos = 1920/2.0f;
    float wiz_y_pos = 1080/2.0f;
    int wiz_move_speed = 200;
    wizard_sprite.setPosition(wiz_x_pos, wiz_y_pos);

    //Defining the origin of the fireball
    FloatRect fireballRect = fireball_sprite.getLocalBounds();
    fireball_sprite.setOrigin(fireballRect.left + fireballRect.width / 2.0f, fireballRect.top + fireballRect.height / 2.0f);


    Vector2f clicked;

    bool start = false;

    Vector2f center_screen;
    center_screen.x = 1920/2;
    center_screen.y = 1080/2;



    //Creating the attack class
    class Attack
    {
        
        vector<int> x_goals;
        vector<int> y_goals;
        vector<float> x_diffs;
        vector<float> y_diffs;
        vector<float> angles;
        vector<float> x_trues;
        vector<float> y_trues;
        vector<int> x_pos;
        vector<int> y_pos;
        vector<bool> dead_attacks;
        vector<float> originate_from_x;
        vector<float> originate_from_y;
        Time time_since_last_shot;
        Time zero_time;
        Clock cooldown;
        float cooldown_time = 0.75;
        int damage = 1;
        int attack_counter = 0;
        int true_dead_attack_counter = 0;
        int attack_travel_speed = 200;

        public:
        void attack_generator(int x_in,int y_in, float wiz_x, float wiz_y)
        {
            if(attack_counter > 0)
            {
                if(time_since_last_shot.asSeconds() > cooldown_time)
                {
                    originate_from_x.push_back(wiz_x);
                    originate_from_y.push_back(wiz_y);
                    x_goals.push_back(x_in);
                    y_goals.push_back(y_in);
                    x_diffs.push_back(x_goals[attack_counter]- wiz_x);
                    y_diffs.push_back(y_goals[attack_counter]- wiz_y);
                    angles.push_back(atan(y_diffs[attack_counter]/x_diffs[attack_counter]));
                    x_trues.push_back(wiz_x);
                    y_trues.push_back(wiz_y);
                    x_pos.push_back(floor(x_trues[attack_counter]));
                    y_pos.push_back(floor(y_trues[attack_counter]));
                    dead_attacks.push_back(false);

                    attack_counter += 1;
                    cout << time_since_last_shot.asSeconds();
                    time_since_last_shot = zero_time;
                }
                else
                {
                    cout << "attack on cooldown";
                }
            }
            else
            {
                originate_from_x.push_back(wiz_x);
                originate_from_y.push_back(wiz_y);
                x_goals.push_back(x_in);
                y_goals.push_back(y_in);
                x_diffs.push_back(x_goals[attack_counter]- wiz_x);
                y_diffs.push_back(y_goals[attack_counter]- wiz_y);
                angles.push_back(atan(y_diffs[attack_counter]/x_diffs[attack_counter]));
                x_trues.push_back(wiz_x);
                y_trues.push_back(wiz_y);
                x_pos.push_back(floor(x_trues[attack_counter]));
                y_pos.push_back(floor(y_trues[attack_counter]));
                dead_attacks.push_back(false);

                attack_counter += 1;
            }
        }
        void attack_manager(Time dt)
        {
            time_since_last_shot += cooldown.restart();

            for (int i = true_dead_attack_counter; i < attack_counter; i++)
            {
                if(dead_attacks[i] == false)
                {

                    //Attack Mover
                    if(x_diffs[i] >= 0)
                    {
                        x_trues[i] += ((cos(angles[i]))*attack_travel_speed*dt.asSeconds());
                        y_trues[i] += ((sin(angles[i]))*attack_travel_speed*dt.asSeconds());
                    }

                    else
                    {
                        x_trues[i] -= ((cos(angles[i]))*attack_travel_speed*dt.asSeconds());
                        y_trues[i] -= ((sin(angles[i]))*attack_travel_speed*dt.asSeconds());
                    }

                    x_pos[i] = floor(x_trues[i]);
                    y_pos[i] = floor(y_trues[i]);
                
                    //Attack Killer
                    if(x_pos[i] > 1920 || x_pos[i] < 0 || y_pos[i] > 1080 || y_pos[i] < 0)
                    {
                        dead_attacks[i] = true;
                    }
                }
            }
        }
        bool is_dead_atk(int i)
        {
            return dead_attacks[i];
        }
        int return_atk_count()
        {
            return attack_counter;
        }
        int return_true_dead_atk_count()
        {
            return true_dead_attack_counter;
        }
        int return_x_pos(int i)
        {
            return x_pos[i];
        }
        int return_y_pos(int i)
        {
            return y_pos[i];
        }


        /*

        ****************
        AN IDEA I HAD
        ****************

        void attack_artist(RenderWindow win)
        {
            for(int i = true_dead_attack_counter; i < attack_counter; i++)
            {
                RectangleShape rect(Vector2f(3,3));
                rect.setPosition(Vector2f(x_pos[i], y_pos[i]));
                rect.setFillColor(Color::Red);
                win.draw(rect);
            }
        }
        */
    };

    //Adding the font we will use
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    //Configuring the instruction text
    Text instruction_text;
    instruction_text.setFont(font);
    instruction_text.setString("LEFT CLICK to Shoot\nWASD to MOVE");
    instruction_text.setCharacterSize(50);
    instruction_text.setFillColor(Color::White);

    //Configuring the point counter text
    Text kill_count_text;
    kill_count_text.setFont(font);
    kill_count_text.setString("Kills: ");
    kill_count_text.setCharacterSize(75);
    kill_count_text.setFillColor(Color::White);

    //Positioning the instruction text
    FloatRect textRect = instruction_text.getLocalBounds();
    instruction_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    instruction_text.setPosition(1920/2.0f, 1080/2.0f);

    

    

    //Positioning the point counter text
    kill_count_text.setPosition(30, 30);

    //Attack Variables
    Attack fireball;

    //Variables to Control TIME
    Clock clock;
    Time dt;

    //Game Loop
    while (window.isOpen())
	{
        
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && start == true)
		{
                    
            wiz_move_up = true;
            wiz_y_pos -= wiz_move_speed*dt.asSeconds();
                    
		}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && start == true)
		{
                    
            wiz_move_left = true;
            wiz_x_pos -= wiz_move_speed*dt.asSeconds();
                    
		}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && start == true)
		{
                    
            wiz_move_down = true;
            wiz_y_pos += wiz_move_speed*dt.asSeconds();
                    
		}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && start == true)
		{
                    
            wiz_move_right = true;
            wiz_x_pos += wiz_move_speed*dt.asSeconds();
                    
		}

        Event event;

        while (window.pollEvent(event))
		{
            //Closing the window
            if (event.type == sf::Event::Closed)
			{
				window.close();
			}

            //Grabbing mouse button inputs for various commands
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
                    //outputting coordinates to the consol for debugging purposes
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    

                    clicked.x = event.mouseButton.x;
					clicked.y = event.mouseButton.y;
                    if(start = true)
                    {
                        fireball.attack_generator(clicked.x, clicked.y, wiz_x_pos, wiz_y_pos);
                    }

                    cout << "Shooting\n";
                    
                    if(start == false)
                    {
                        start = true;
                    }
				}
			}   
		}

        //Giving an alternative way of closing the program
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

        /*
        ****************************************
        Update the scene
        ****************************************
        */
        
        //Measure time
        dt = clock.restart();



        if(start == true)
        {
            //Managing Attacks
            fireball.attack_manager(dt);
            //Moving the wizard
            wizard_sprite.setPosition(wiz_x_pos, wiz_y_pos);
        }

        /*
        ****************************************
        Draw the scene
        ****************************************
        */
        
        ///loop through vectors and draw each coordinate
        // Clear everything from the last run frame
        
        window.clear();
        // Draw our game scene here

        //Drawing Background
        window.draw(background_sprite);

        //Drawing Player Character
        window.draw(wizard_sprite);

        //Drawing Point Counter
        window.draw(kill_count_text);

        //Drawing Instruction Text
        if(start == false)
        {
            window.draw(instruction_text);
        }
        
        for(int i = fireball.return_true_dead_atk_count(); i < fireball.return_atk_count(); i++)
        {
            if(fireball.is_dead_atk(i) != true)
            {
                fireball_sprite.setPosition(Vector2f(fireball.return_x_pos(i), fireball.return_y_pos(i)));
                window.draw(fireball_sprite);
            }
        }
        
        
        window.display();
    }

    return 0;
}