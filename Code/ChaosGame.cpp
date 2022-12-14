#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
using namespace std;

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
    Texture wizard_weapon_texture;
    Texture wizard_robe_texture;
    Texture fireball_texture;
    Texture attack_time_bar_border_texture;
    Texture target_dummy_right_texture;
    Texture target_dummy_left_texture;

    //Loading Graphics
    background_texture.loadFromFile("Graphics/Sprite-0002-Unfinished-Pixel-Arena-1920-1080.png");
    wizard_texture.loadFromFile("Graphics/Sprite-0008-64x-WIP-Wizard-Move_Down.png");
    wizard_weapon_texture.loadFromFile("Graphics/Sprite-0012-64x-Floating-Crystal.png");
    fireball_texture.loadFromFile("Graphics/Sprite-0017-Fireball-02.png");
    wizard_robe_texture.loadFromFile("Graphics/Sprite-0010-64x-Wizard-Robe-Fancy.png");
    attack_time_bar_border_texture.loadFromFile("Graphics/Sprite-0014-Timer-Bar.png");
    target_dummy_right_texture.loadFromFile("Graphics/Sprite-0016-Target-Dummy-Looking-Right.png");
    target_dummy_left_texture.loadFromFile("Graphics/Sprite-0015-Target-Dummy-Looking-Left.png");

    //Creating Sprites
    Sprite background_sprite;
    Sprite wizard_sprite;
    Sprite wizard_weapon_sprite;
    Sprite fireball_sprite;
    Sprite wizard_robe_sprite;
    Sprite attack_time_bar_border_sprite;
    Sprite target_dummy_right_sprite;
    Sprite target_dummy_left_sprite;

    //Attaching Textures To Sprites
    background_sprite.setTexture(background_texture);
    wizard_sprite.setTexture(wizard_texture);
    wizard_weapon_sprite.setTexture(wizard_weapon_texture);
    fireball_sprite.setTexture(fireball_texture);
    wizard_robe_sprite.setTexture(wizard_robe_texture);
    attack_time_bar_border_sprite.setTexture(attack_time_bar_border_texture);
    target_dummy_right_sprite.setTexture(target_dummy_right_texture);
    target_dummy_left_sprite.setTexture(target_dummy_left_texture);

    //Positioning Sprites
    background_sprite.setPosition(0,0);
    attack_time_bar_border_sprite.setPosition(1920 - 290, 0 + 78);

    //POSITIONING PLAYER CHARACTER
    float wiz_x_pos = 1920/2.0f;
    float wiz_y_pos = 1080/2.0f;

    //Positioning the wizard's robe
    FloatRect wizRobeRect = wizard_robe_sprite.getLocalBounds();
    wizard_robe_sprite.setOrigin(wizRobeRect.left + wizRobeRect.width / 2.0f, (wizRobeRect.top + wizRobeRect.height / 2.0f) - 100);
    wizard_robe_sprite.setPosition(wiz_x_pos, wiz_y_pos);
        //Changing it's size(not now)
    wizard_robe_sprite.setScale(0.7,0.6);

    //Positioning the wizard's weapon
    FloatRect wizWeaponRect = wizard_weapon_sprite.getLocalBounds();
    wizard_weapon_sprite.setOrigin(wizWeaponRect.left + wizWeaponRect.width / 2.0f, (wizWeaponRect.top + wizWeaponRect.height / 2.0f) - 40);
    wizard_weapon_sprite.setPosition(wiz_x_pos, wiz_y_pos);
        //Changing it's size(not now)
    wizard_weapon_sprite.setScale(1,1);

    //Positioning the Wizard
    FloatRect wizRect = wizard_sprite.getLocalBounds();
    wizard_sprite.setOrigin(wizRect.left + wizRect.width / 2.0f, wizRect.top + wizRect.height / 2.0f);
    bool wiz_move_up = false;
    bool wiz_move_left = false;
    bool wiz_move_right = false;
    bool wiz_move_down = false;
    int wiz_move_speed = 250;
    wizard_sprite.setPosition(wiz_x_pos, wiz_y_pos);
        //Changing its size(not now)
    wizard_sprite.setScale(1,1);

    //Defining the origin of the fireball
    FloatRect fireballRect = fireball_sprite.getLocalBounds();
    fireball_sprite.setOrigin(fireballRect.left + fireballRect.width / 2.0f, fireballRect.top + fireballRect.height / 2.0f);

    //On Mice, not men
    Vector2f clicked;
    Mouse cursor;
    Vector2i mouse_pos;
    Vector2f mouse_char_diff;
    float wiz_weapon_angle_to_cursor;
    float wiz_weapon_angle_to_cursor_degrees;

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
        int attack_travel_speed = 500;

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
        float return_time_since_last_shot()
        {
            return time_since_last_shot.asSeconds();
        }
        float return_total_cooldown()
        {
            return cooldown_time;
        }
        bool is_dead_atk(int i)
        {
            return dead_attacks[i];
        }
        int return_atk_count()
        {
            return attack_counter;
        }
        int return_true_dead()
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
        void kill_attack(int i)
        {
            dead_attacks[i] = true;
        }
        int return_damage()
        {
            return damage;
        }
    };

    //Creating the enemy class
    class Enemy
    {
        vector<string> enemy_name;
        vector<int> x_goals;
        vector<int> y_goals;
        vector<float> x_diffs;
        vector<float> y_diffs;
        vector<int> x_pos;
        vector<int> y_pos;
        vector<int> current_health;
        vector<bool> elite_status;
        vector<int> max_health;
        vector<float> angles;
        vector<bool> alive;
        vector<bool> face_left;
        vector<float> size_scale_factor;
        vector<int> enemy_travel_speed;
        vector<int> hitbox;
        int enemy_counter = 0;
        int generation_buffer = 50;
        int player_generation_buffer = 200;
        int randomization_counter = 0;
        int enemies_dead = 0;
        public:
        //Generates an enemy
        /*
        *******************************************************************************************************************
        VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
        *******************************************************************************************************************

                                                        ENEMY GENERATOR IS

                                                        CURENTLY BROKEN
                                                        
                                                        (CORE DUMP)

                                                        PLEASE FIX

        *******************************************************************************************************************
        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        *******************************************************************************************************************
        */
        void generate_enemy(int wiz_x_pos,int wiz_y_pos)
        {
            enemy_name.push_back("Target Dummy");
            if(enemy_name[enemy_counter] == "Target Dummy")
            {
                cout << "step 1";
                //Determining if the enemy will be elite
                srand(time(0) + randomization_counter);
                if(rand() % 10 == 9)
                {
                    elite_status.push_back(true);
                }
                else
                {
                    elite_status.push_back(false);
                }

                cout << "step 2";

                //Setting enemy name, health, alive status, travel speed and max health also hitbox size
                enemy_travel_speed.push_back(150);
                //Not right now
                //enemy_name.push_back(name);
                alive.push_back(true);
                hitbox.push_back(35);
                if(elite_status[enemy_counter] == false)
                {
                    max_health.push_back(25);
                    current_health.push_back(max_health[enemy_counter]);
                }
                else
                {
                    max_health.push_back(5);
                    current_health.push_back(max_health[enemy_counter]);
                }

                cout << "step 3";

                //Randomly Generating the starting position so it doesnt overlap the player or end up outside the walls
                srand(time(0));
                randomization_counter = 0;
                x_pos.push_back(generation_buffer + (rand() % 1920 - 2*generation_buffer));
                y_pos.push_back(generation_buffer + (rand() % 1080 - 2*generation_buffer));

                cout << "step 4";

                while(abs(x_pos[enemy_counter] - wiz_x_pos) <= player_generation_buffer || abs(y_pos[enemy_counter] - wiz_y_pos) <= player_generation_buffer)
                {
                    srand(time(0) + randomization_counter);

                    x_pos.erase(x_pos.end() - 1);
                    y_pos.erase(y_pos.end() - 1);
                    x_pos.push_back(generation_buffer + (rand() % 1920 - 2*generation_buffer));
                    y_pos.push_back(generation_buffer + (rand() % 1080 - 2*generation_buffer));

                    //variable to help change the random seed each time to make sure the positions are different even if the time is effectivly the same
                    randomization_counter += 1;
                }

                cout << "step 5";

                //Generating placeholder information to maintain shared vector positions
                x_goals.push_back(wiz_x_pos);
                y_goals.push_back(wiz_y_pos);
                x_diffs.push_back(wiz_x_pos - x_pos[enemy_counter]);
                y_diffs.push_back(wiz_y_pos - y_pos[enemy_counter]);
                if(x_diffs[enemy_counter] > 0)
                {
                    face_left.push_back(false);
                }
                else
                {
                    face_left.push_back(true);
                }
                if(elite_status[enemy_counter] = true)
                {
                    size_scale_factor.push_back(1.5);
                }
                else
                {
                    size_scale_factor.push_back(1.0f);
                }
                angles.push_back(atan(y_diffs[enemy_counter]/x_diffs[enemy_counter]));

                cout << "step 6";

            }
            enemy_counter += 1;
        }
        void enemy_movement_manager(int wiz_x_pos,int wiz_y_pos, Time dt)
        {
            //Enemy Type Brancher
            for (int i = 0; i < enemy_counter; i++)
            {
                //Movement
                x_goals[i] = wiz_x_pos;
                y_goals[i] = wiz_y_pos;
                x_diffs[i] = wiz_x_pos - x_pos[i];
                y_diffs[i] = wiz_y_pos - y_pos[i];
                angles[i] = (atan(y_diffs[i]/x_diffs[i]));
                if(x_diffs[i] >= 0)
                {
                    face_left[i] = false;
                    x_pos[i] += enemy_travel_speed[i]*cos(angles[i])*dt.asSeconds();
                    y_pos[i] += enemy_travel_speed[i]*sin(angles[i])*dt.asSeconds();
                }
                else
                {
                    face_left[i] = true;
                    x_pos[i] -= enemy_travel_speed[i]*cos(angles[i])*dt.asSeconds();
                    y_pos[i] -= enemy_travel_speed[i]*sin(angles[i])*dt.asSeconds();
                }
            }
        }
        void enemy_damage_manager(Attack attack)
        {
            //Taking Damage and dying
            for(int i = 0; i < enemy_counter; i++)
            {
                if(alive[i] == true)
                {
                    for(int j = attack.return_true_dead(); j < attack.return_atk_count(); j++)
                    {
                        if(attack.is_dead_atk(j) != true)
                        {
                            if(abs(x_pos[i] - attack.return_x_pos(j)) < hitbox[i] || abs(y_pos[i] - attack.return_y_pos(j)) < hitbox[i])
                            {
                                attack.kill_attack(j);
                                if (attack.is_dead_atk(j) == true)
                                {
                                    cout << "IT WORKS!!!";
                                }
                                current_health[i] -= attack.return_damage();
                                if(current_health[i] <= 0)
                                {
                                    alive[i] = false;
                                    enemies_dead += 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        int return_enemy_count()
        {
            return enemy_counter;
        }
        int return_true_dead()
        {
            return enemies_dead;
        }
        bool return_alive(int i)
        {
            return alive[i];
        }
        bool return_face_left(int i)
        {
            return face_left[i];
        }
        string return_name(int i)
        {
            return enemy_name[i];
        }
        int return_x_pos(int i)
        {
            return x_pos[i];
        }
        int return_y_pos(int i)
        {
            return y_pos[i];
        }
    };

    //Adding the font we will use
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    //Configuring attack timer label
    Text attack_timer_text;
    attack_timer_text.setFont(font);
    attack_timer_text.setString("Fireball Charge");
    attack_timer_text.setCharacterSize(20);
    attack_timer_text.setFillColor(Color::White);

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

    //Positioning the attack timer label
    FloatRect attackTimerRect = attack_timer_text.getLocalBounds();
    attack_timer_text.setOrigin(attackTimerRect.left + attackTimerRect.width / 2.0f, attackTimerRect.top + attackTimerRect.height / 2.0f);
    attack_timer_text.setPosition(1920 - ((attackTimerRect.width / 2.0f) + 100), 0 + ((attackTimerRect.height / 2.0f) + 60));

    //Positioning the instruction text
    FloatRect textRect = instruction_text.getLocalBounds();
    instruction_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    instruction_text.setPosition(1920/2.0f, 1080/2.0f);

    
    //Positioning the point counter text
    kill_count_text.setPosition(30, 30);

    //Wall Buffer
    int wall_buffer = 75;

    //Attack Variables
    Attack fireball;

    //Enemy Variables
    Enemy enemy;

    //Variables to Control TIME
    Clock clock;
    Time dt;
    float time_collector;

    //Making attack timer bar
    RectangleShape attackTimeBar;
    float attackTimeBarStartWidth = 130;
    float attackTimeBarStartHeight = 24;
    attackTimeBar.setSize(Vector2f(attackTimeBarStartWidth, attackTimeBarStartHeight));
    attackTimeBar.setFillColor(Color::Red);
    attackTimeBar.setPosition(1920 - 128 - attackTimeBarStartWidth, 0 + 76 + attackTimeBarStartHeight);
    float attackTimeBarWidthPerSecond = attackTimeBarStartWidth / fireball.return_total_cooldown();

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

        //Refreshing attack time bar
        if(fireball.return_time_since_last_shot() < fireball.return_total_cooldown())
        {
            attackTimeBar.setSize(Vector2f(attackTimeBarWidthPerSecond*(fireball.return_time_since_last_shot()), attackTimeBarStartHeight));
        }
        else
        {
            attackTimeBar.setSize(Vector2f(attackTimeBarStartWidth, attackTimeBarStartHeight));
        }



        if(start == true)
        {

            //Managing Attacks
            fireball.attack_manager(dt);

            //Creating a timer that resets every 5 sec
            time_collector += dt.asSeconds();
            if(time_collector >= 5)
            {
                enemy.generate_enemy(wiz_x_pos, wiz_y_pos);
                time_collector = 0;
            }

            //Managing Enemies
            enemy.enemy_movement_manager(wiz_x_pos, wiz_y_pos, dt);
            enemy.enemy_damage_manager(fireball);

            
            //Moving the wizard
            if(wiz_x_pos > 1920-wall_buffer)
            {
                wiz_x_pos -= wiz_move_speed*dt.asSeconds();
            }
            if(wiz_y_pos > 1080 - 50 - wall_buffer)
            {
                wiz_y_pos -= wiz_move_speed*dt.asSeconds();
            }
            if(wiz_x_pos < 0 + wall_buffer)
            {
                wiz_x_pos += wiz_move_speed*dt.asSeconds();
            }
            if(wiz_y_pos < -75 + wall_buffer)
            {
                wiz_y_pos += wiz_move_speed*dt.asSeconds();
            }


            wizard_sprite.setPosition(wiz_x_pos, wiz_y_pos);
            wizard_weapon_sprite.setPosition(wiz_x_pos, wiz_y_pos);
            wizard_robe_sprite.setPosition(wiz_x_pos, wiz_y_pos);

            //Rotating the Wizard's Weapon
                //Locating the cursor

            //NOT CURRENTLY IN USE
            //mouse_pos = cursor.getPosition(window);
            //mouse_char_diff.x = mouse_pos.x - wiz_x_pos;
            //mouse_char_diff.y = mouse_pos.y - wiz_y_pos;
            //wiz_weapon_angle_to_cursor = atan(mouse_char_diff.y/mouse_char_diff.x);
            //wiz_weapon_angle_to_cursor_degrees = (wiz_weapon_angle_to_cursor/(2*3.141592653589))*360;

            //Rotating Automatically
            if(wiz_weapon_angle_to_cursor > 2*3.141592653589)
            {
                wiz_weapon_angle_to_cursor -= 2*3.141592653589;
            }
            wiz_weapon_angle_to_cursor += 2*dt.asSeconds();
            if(mouse_char_diff.x > 0)
            {
                wizard_weapon_sprite.setPosition(wiz_x_pos + (150)*cos(wiz_weapon_angle_to_cursor),wiz_y_pos + (150)*sin(wiz_weapon_angle_to_cursor));
                //NOT CURRENTLY IN USE
                //wizard_weapon_sprite.setRotation(wiz_weapon_angle_to_cursor_degrees-90);
            }
            else
            {
                wizard_weapon_sprite.setPosition(wiz_x_pos - (150)*cos(wiz_weapon_angle_to_cursor),wiz_y_pos - (150)*sin(wiz_weapon_angle_to_cursor));
                //NOT CURRENTLY IN USE
                //wizard_weapon_sprite.setRotation(wiz_weapon_angle_to_cursor_degrees-270);
            }
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
        window.draw(wizard_weapon_sprite);
        window.draw(wizard_robe_sprite);

        //Drawing Point Counter
        window.draw(kill_count_text);

        //Drawing attack timer label
        window.draw(attack_timer_text);

        //Drawing attack timer bar
        window.draw(attackTimeBar);
        window.draw(attack_time_bar_border_sprite);

        //Drawing enemies
        for(int i = enemy.return_true_dead(); i < enemy.return_enemy_count(); i++)
        {
            if(enemy.return_alive(i) == true)
            {
                if(enemy.return_face_left(i) == true)
                {
                    target_dummy_left_sprite.setPosition(Vector2f(enemy.return_x_pos(i), enemy.return_y_pos(i)));
                    window.draw(target_dummy_left_sprite);
                }
                else
                {
                        target_dummy_right_sprite.setPosition(Vector2f(enemy.return_x_pos(i), enemy.return_y_pos(i)));
                        window.draw(target_dummy_right_sprite);
                }
            }
        }

        //Drawing Attacks
        for(int i = fireball.return_true_dead(); i < fireball.return_atk_count(); i++)
        {
            if(fireball.is_dead_atk(i) != true)
            {
                fireball_sprite.setPosition(Vector2f(fireball.return_x_pos(i), fireball.return_y_pos(i)));
                window.draw(fireball_sprite);
            }
        }

        //Wizards Hat Drawn Last
        window.draw(wizard_sprite);

        //Drawing Instruction Text
        if(start == false)
        {
            window.draw(instruction_text);
        }
        
        
        
        window.display();
    }

    return 0;
}