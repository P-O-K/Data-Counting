
#include <iostream>
#include <map>


class Node
{
public:

    int     VALUE   =0;
    int     COUNT   =0;
    Node*   LEFT    =NULL;
    Node*   RIGHT   =NULL;


    Node( int value ) : VALUE( ( int )value ), COUNT( 1 ) { }



    ~Node(  ){ delete LEFT; delete RIGHT; }
};





class CollectionTree
{

public:

    Node*   ROOT    =NULL;


    CollectionTree( int value ) : ROOT( new Node( (int)value ) ) { return; }



    void includeString( const std::string& string )
    {
        for( char const& ch : string  )
        {
            include( ( int )ch );
        }
        return;
    }



    void include( int value )
    {
        Node* node = includeHandle( ROOT, value );

        if( value < node->VALUE )
        {
            node->LEFT = new Node( value );
        }
        else if( value > node->VALUE )
        {
            node->RIGHT = new Node( value );
        }
        else if( value == node->VALUE )
        {
            ++node->COUNT;
        }
        return;
    }



    Node* includeHandle( Node* node, int value )                        // returns self if exists else parent;
    {
        if( node != NULL )
        {
            if( value < node->VALUE )
            {
                if( node->LEFT )
                {
                    return includeHandle( node->LEFT, value );
                }
            }
            if( value > node->VALUE )
            {
                if( node->RIGHT )
                {
                    return includeHandle( node->RIGHT, value );
                }
            }
        }
        return node;
    }



    void reverseTree( void )
    {
        reverseTreeHandle( ROOT );
        return;
    }



    void reverseTreeHandle( Node* node )
    {
        if( node == NULL ){
            return;
        }
        
        reverseTreeHandle( node->LEFT );
        reverseTreeHandle( node->RIGHT );

        Node* temp = node->LEFT;
        node->LEFT = node->RIGHT;
        node->RIGHT = temp;

        return;

    }



    void renderIntTree( )
    {
        std::map< int, int > dict;          // < N->VALUE, N->COUNT >
        renderTreeHandle( ROOT, dict );
        return;
    }


    void renderAsciiTree( )
    {
        std::map< char, int > dict;          // < N->VALUE, N->COUNT >
        renderTreeHandle( ROOT, dict );
        return;
    }



    template< typename typeDef >
    void renderTreeHandle( Node* node, std::map< typeDef, int > &dict )
    {
        getCollectionHandle( node, dict );
        for( auto&& data = dict.begin( ) ; data != dict.end( ) ; ++data )
        {
            std::cout << data->first << " -> " << data->second << '\n';
        }
        return;
    }



    std::map< int, int > getIntCollection( )
    { 
        std::map< int, int > dict;          // < N->VALUE, N->COUNT >
        getCollectionHandle( ROOT, dict );
        return dict;
    }



    std::map< char, int > getAsciiCollection( )
    { 
        std::map< char, int > dict;          // < N->VALUE, N->COUNT >
        getCollectionHandle( ROOT, dict );
        return dict;
    }



    template< typename typeDef >
    void getCollectionHandle( Node* node, std::map< typeDef ,int >& dict )
    {
        if( node->LEFT )
        {
            getCollectionHandle( node->LEFT, dict );
        }

        dict.insert( { ( typeDef )node->VALUE, node->COUNT } );

        if( node->RIGHT )
        {
            getCollectionHandle( node->RIGHT, dict );
        }

        return;
    }



    Node* locate( int value )
    {
        return includeHandle( ROOT, ( int )value );
    }



    ~CollectionTree( ){ delete ROOT; }
};




int main( void )
{
    CollectionTree CLT( 'p' );      // Initialized with ROOT value

    CLT.includeString( "Sample, Lets include this string -> message!" );

    CLT.include( 'a' );
    CLT.include( 's' );
    CLT.include( 'd' );
    CLT.include( 'f' );
    CLT.include( 126 );
    CLT.include( 7898 );
    CLT.include( 51468 );


    // Render int values of tree
    CLT.renderIntTree( );
    std::cout << std::endl;

    // Retrieve and display ascii values of tree...
    // CLT.renderAsciiTree( )
    std::map< char, int > dict = CLT.getAsciiCollection( );
    for( auto&& ix = dict.begin( ) ; ix != dict.end( ) ; ++ix )
    {
          std::cout << ix->first << " -> " << ix->second << '\n';
    }

    return 0;
}