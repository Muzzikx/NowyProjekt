#pragma once

#include <iostream>

class guiMenager
{
	std::vector<s_button> buttons;
	std::vector<s_inputText> inputText;
	std::vector<s_label> labels;

	sf::Font font;
	sf::Font arial;
public:
	guiMenager();
	void checkEvent( );
	void draw();
	void add( std::string type, sf::Vector2f position , sf::Vector2f size, std::string name );
	int getClickedButton();
	std::string getInputText( int id );
	

};

guiMenager::guiMenager()
{
	font.loadFromFile( DEFAULT_FONT_PATH );
	arial.loadFromFile( ARIAL_FONT_PATH );
}


std::string guiMenager::getInputText( int id )
{
	if( id >= 0 && id <inputText.size() ) return inputText[id].name.getString();
	else return "";
}


void guiMenager::checkEvent( )
{
	if( event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ){
		for( int i=0; i<buttons.size(); i++ )
			if( buttons[i].isActived ) buttons[i].isClicked = true;
		
		for( int i=0; i<inputText.size(); i++ )
			if(inputText[i].shape.getGlobalBounds().contains( sf::Vector2f( mouse.getPosition( window )) ))inputText[i].isActived = true;
			else inputText[i].isActived = false;
	}

	if ( event.type == sf::Event::TextEntered )
	{
		for( int i=0; i<inputText.size(); i++ )
			if( inputText[i].isActived )
			{
				std::string newString;
				switch (event.text.unicode)
				{
				case 13:
					inputText[i].isActived = false;
					break;
				case 8:
					if( inputText[i].name.getString().getSize() > 0){
						newString.append( inputText[i].name.getString(), 0, inputText[i].name.getString().getSize()-1 );
						inputText[i].name.setString( newString );
					}
					break;
				default:
					if( inputText[i].name.getLocalBounds().width < (inputText[i].shape.getLocalBounds().left + inputText[i].shape.getLocalBounds().width - 30) )
						inputText[i].name.setString( inputText[i].name.getString() + (inputText[i].isPass ? '*' : static_cast<char>(event.text.unicode) ) );
					break;
				}
			}
	}
		
	for( int i=0; i<buttons.size(); i++ )
		if( buttons[i].shape.getGlobalBounds().contains( sf::Vector2f( mouse.getPosition( window ) ) ) ) buttons[i].isActived = true;
		else buttons[i].isActived = false;
}

int guiMenager::getClickedButton()
{
	for( int i=0; i<buttons.size(); i++ )
		if( buttons[i].isClicked ){ 
			buttons[i].isClicked = false;
			return i;
	}
	return -1;
}

void guiMenager::draw() 
{
	for( int i=0; i<buttons.size(); i++ )
		if( buttons[i].isActived ) buttons[i].shape.setOutlineColor( COLOR_BUTTON_OUT );
		else buttons[i].shape.setOutlineColor( COLOR_TRANSPARENT );
	
	for( int i=0; i<inputText.size(); i++ )
		if( inputText[i].isActived ) inputText[i].shape.setOutlineColor( COLOR_TEXTINPUT_OUT );
		else inputText[i].shape.setOutlineColor( COLOR_TRANSPARENT );

	for( int i=0; i<buttons.size(); i++ )
	{
		window.draw( buttons[i].shape );
		window.draw( buttons[i].name );
	}

	for( int i=0; i<inputText.size(); i++ )
	{
		window.draw( inputText[i].shape );
		window.draw( inputText[i].name );
	}

	for( int i=0; i<labels.size(); i++ )
	{
		window.draw( labels[i].name );
	}
}

void guiMenager::add( std::string type, sf::Vector2f position=sf::Vector2f(100,100) , sf::Vector2f size=sf::Vector2f(100,100), std::string name="default" )
{
	if( type == "button" ){
		buttons.push_back( s_button() );
		buttons.back().name.setFont( font );
		buttons.back().name.setString( name );
		buttons.back().name.setOrigin( buttons.back().name.getGlobalBounds().width/2, buttons.back().name.getCharacterSize()/1.7 );
		buttons.back().name.setPosition( position );
		buttons.back().name.setColor( sf::Color::White );

		buttons.back().shape.setSize( size );
		buttons.back().shape.setOrigin( size.x/2, size.y/2 );
		buttons.back().shape.setPosition( position );
		buttons.back().shape.setFillColor( COLOR_BUTTON_IN );
		buttons.back().shape.setOutlineThickness( 2 );
		buttons.back().shape.setOutlineColor( COLOR_TRANSPARENT );

		buttons.back().isActived = false;
		buttons.back().isClicked = false;
	}
	else if( type == "inputText" )
	{
		inputText.push_back( s_inputText() );
		inputText.back().name.setFont( arial );
		
		inputText.back().name.setOrigin( ( size.x/2.1 ), buttons.back().name.getCharacterSize()/1.7 );
		inputText.back().name.setPosition( position );
		inputText.back().name.setColor( sf::Color::White );

		inputText.back().shape.setSize( size );
		inputText.back().shape.setOrigin( size.x/2, size.y/2 );
		inputText.back().shape.setPosition( position );
		inputText.back().shape.setFillColor( COLOR_TEXTINPUT_IN );
		inputText.back().shape.setOutlineThickness( 2 );
		inputText.back().shape.setOutlineColor( COLOR_TRANSPARENT );

		inputText.back().isActived = false;
		if( name == "*" ) inputText.back().isPass = true;
		else inputText.back().isPass = false;
		name = "";
		inputText.back().name.setString( name );
	} 
	else if( type == "label" )
	{
		labels.push_back( s_label() );
		labels.back().name.setFont( font );
		labels.back().name.setString( name );
		labels.back().name.setOrigin( labels.back().name.getGlobalBounds().width/2 , labels.back().name.getCharacterSize()/1.7 );
		labels.back().name.setPosition( position );
		labels.back().name.setColor( sf::Color::White );
	}
}
