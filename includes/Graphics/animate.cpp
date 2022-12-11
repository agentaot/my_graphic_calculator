#include "animate.h"
    
    //run application 
    void Animate::run(){
        i = 0;
        j = 2;
        Mousein = false;
        graph.Eq = "";
        create_new_graph();
        while(window.isOpen()){
            text.setFillColor(sf::Color::Red);
            text.setPosition(sf::Vector2f(30,SCREEN_HEIGHT/6+30));
            text.setFont(font);
            text.setStyle(sf::Text::Bold);
            text.setCharacterSize(60);
            font.loadFromFile("Roboto-Thin.ttf");

            process_events();
            update();
            render();
        }
    }

    void Animate::Draw(){
        system.Draw(window);
        sidebar.draw(window);
        if(take_input){
            window.draw(input_box());
        }
        window.draw(text);
        gui.set_axis_labels(window);
        window.draw(sidebar.create_button(i,j));

        
    }
    //clear->draw->display cycle
    void Animate::render(){
        window.clear(sf::Color(20, 20, 20,255));
        Draw();
        window.display();
    }

    void Animate::update(){
        sidebar.set_bottom_Bar_info(info,window,Mousein);
        gui.set_graph_info(info);
        // Translator T;
        // T.set_graph_info(info);
        // cout<<endl;
        // cout<<T.sfml_to_cart(sf::Vector2f(SCREEN_HEIGHT/2,SCREEN_HEIGHT/2)).x;
        // cout<<",";
        // cout<<T.sfml_to_cart(sf::Vector2f(SCREEN_HEIGHT/2,SCREEN_HEIGHT/2)).y;

        
    }

    void Animate::process_events(){
        sf::Event event;
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                window.close();
                break;
                case sf::Event::TextEntered:{
                    if(event.text.unicode == '\b'){
                        input.pop_back();
                    }
                    else if(event.text.unicode == '\t'){
                        take_input = !take_input;
                        if(!take_input){
                            text.setString(input);
                        }   
                    }
                    else if(event.text.unicode == '\n'){
                        if(take_input==true){
                        graph.set_string(input);   
                        input = "";
                        text.setString("");
                        take_input = false;
                        }
                    }
                    else if (event.text.unicode<128){
                        if(take_input){
                            input += event.text.unicode;
                        }
                    }
                    if(take_input){
                        if(strlen(input.c_str())>45){
                            text.setString(input.substr(strlen(input.c_str())-45,45));
                        }
                        else{
                            text.setString(input);
                        }
                    }
                    else{
                        text.setString("");
                    }
                   // cout<<input<<endl;
                }
                break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Left){
                        info->set_offset(-1,0);
                    }
                    else if(event.key.code == sf::Keyboard::Right){
                        info->set_offset(1,0);
                    }
                    else if(event.key.code == sf::Keyboard::Up){
                        info->set_offset(0,-1);
                    }
                    else if(event.key.code == sf::Keyboard::Down){
                        info->set_offset(0,1);
                    }
                    else if(event.key.code == sf::Keyboard::Space){
                        info->set_offset(-info->x_offset.y,-info->y_offset.y);
                    }
                    else if(event.key.code == sf::Keyboard::P){
                        info->set_scale(1,0);
                        info->offset_recalculate();
                    }
                    else if(event.key.code == sf::Keyboard::O){
                        info->set_scale(-1,0);
                        info->offset_recalculate();
                    }
                    break;
                case sf::Event::Resized:
                    graph.set_window(window.getSize().x,window.getSize().y);
                    cout<<window.getSize().x<<"|";
                    cout<<window.getView().getSize().x<<"|";
                    cout<<window.getSize().y<<"|";
                    cout<<window.getView().getSize().y<<endl;
                    break;
                case sf::Event::MouseMoved:
                    Mousein = true;
                    if(sf::Mouse::getPosition(window).x>WORK_PANEL){
                        Mousein = false;
                        i = 1;
                        j = -1;
                        int Mouse_y = (sf::Mouse::getPosition(window).y);
                        while(Mouse_y>0){
                            Mouse_y = Mouse_y-(BUTTON_SIZE);
                            j++;
                        }
                        if(j>8){
                            j=8;
                        }
                        else if(j<2){
                            j=2;
                        }
                    }
                    else{
                        i = 0;
                    }
                case sf::Event::MouseButtonPressed:
                    
                    break;
                default:
                    break;

            }
        }
    }

void Animate::create_new_graph(){
    info = &graph;
    system.set_graph_info(info);
}


 sf::RectangleShape Animate::input_box(){
    sf::RectangleShape input_box;
    input_box.setFillColor(sf::Color(0,240,0,50));
    input_box.setPosition(sf::Vector2f(0,(SCREEN_HEIGHT/6)));
    input_box.setSize(sf::Vector2f(WORK_PANEL,(SCREEN_HEIGHT/6)));
    return input_box;
}

