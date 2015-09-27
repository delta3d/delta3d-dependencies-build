#define BOOST_TEST_MODULE GNETests
#include <boost/test/included/unit_test_framework.hpp>

#include <iostream>
#include <gnelib.h>

using namespace std;
using namespace GNE;

class TestConnection : public Connection {
public:
  void addHeader(Buffer& raw) { Connection::addHeader(raw); }
  void addVersions(Buffer& raw) { Connection::addVersions(raw); }
};

/**
 * Check that all of the HawkNL types that are used for network communication
 * have their expected sizes. These should hold regardless of architecture.
 */
BOOST_AUTO_TEST_CASE( hawknl_types_check ) {
  BOOST_CHECK_EQUAL( sizeof(NLbyte), 1 );
  BOOST_CHECK_EQUAL( sizeof(NLubyte), 1 );
  BOOST_CHECK_EQUAL( sizeof(NLshort), 2 );
  BOOST_CHECK_EQUAL( sizeof(NLushort), 2 );
  BOOST_CHECK_EQUAL( sizeof(NLlong), 4 );
  BOOST_CHECK_EQUAL( sizeof(NLulong), 4 );
  BOOST_CHECK_EQUAL( sizeof(NLint), 4 );
  BOOST_CHECK_EQUAL( sizeof(NLuint), 4 );
  BOOST_CHECK_EQUAL( sizeof(NLenum), 4 );
}

/**
 * Check that all of the GNE types that are used for network communication
 * have their expected sizes. These should hold regardless of architecture.
 */
BOOST_AUTO_TEST_CASE( gne_types_check ) {
  BOOST_CHECK_EQUAL( sizeof(gbyte), 1 );
  BOOST_CHECK_EQUAL( sizeof(gbool), 1 );
  BOOST_CHECK_EQUAL( sizeof(gint16), 2 );
  BOOST_CHECK_EQUAL( sizeof(guint16), 2 );
  BOOST_CHECK_EQUAL( sizeof(gint32), 4 );
  BOOST_CHECK_EQUAL( sizeof(guint32), 4 );
  BOOST_CHECK_EQUAL( sizeof(gsingle), 4 );
  BOOST_CHECK_EQUAL( sizeof(gdouble), 8 );
}

BOOST_AUTO_TEST_CASE( hawknl_endian_define_check ) {
  gint16 val = 0x1122;
  gbyte* valraw = (gbyte*)&val;
#ifdef NL_LITTLE_ENDIAN
  BOOST_CHECK_EQUAL( 0x22, valraw[0] );
#else
  BOOST_CHECK_EQUAL( 0x11, valraw[0] );
#endif
}

BOOST_AUTO_TEST_CASE( gne_first_packet ) {
  GNE::initGNE( NL_IP, atexit, 1000 );
  GNE::setGameInformation( "UnitTest", 0x11223344 );

  gint16 val = 0x1122;
  val = nlSwaps( val ); //now val should be little endian
  gbyte* valraw = (gbyte*)&val;
  BOOST_CHECK_MESSAGE( 0x22 == valraw[0], "nlSwaps did not convert value to little endian as expected, check HawkNL code" );
  BOOST_CHECK_EQUAL( 0x22, valraw[0] );

  Buffer buf = Buffer();
  TestConnection conn = TestConnection();

  conn.addHeader( buf );
  conn.addVersions( buf );

  gbyte* data = buf.getData();

  gbyte expected[] = { 'G', 'N', 'E',
    0, 0, 7, 0, //major, minor, build*2 = 7
    //32 bytes game name
    'U', 'n', 'i', 't', 'T', 'e', 's', 't', 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //user version (little endian)
    0x44, 0x33, 0x22, 0x11};

  int expectedSize = sizeof(expected)/sizeof(expected[0]);

  BOOST_CHECK_EQUAL( expectedSize, buf.getPosition() );
  BOOST_CHECK_EQUAL_COLLECTIONS( data, data+expectedSize, expected, expected+expectedSize );

  GNE::shutdownGNE();
}