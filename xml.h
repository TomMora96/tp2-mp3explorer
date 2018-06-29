/* xml.h */

#ifndef XML__H
#define XML__H

#define XML_CONTEXT_TRACK_TAG_POS 0
#define XML_CONTEXT_NAME_TAG_POS 1
#define XML_CONTEXT_ARTIST_TAG_POS 2
#define XML_CONTEXT_GENRE_TAG_POS 3

#define XML_CONTEXT_MAX_TAGS 4

#define XML_CONTEXT_TRACK_TAG "track"
#define XML_CONTEXT_NAME_TAG "name"
#define XML_CONTEXT_ARTIST_TAG "artist"
#define XML_CONTEXT_GENRE_TAG "genre"

#define XML_HEADER "xml_header.txt"
#define XML_FOOTER "xml_footer.txt"

char * xml_context[XML_CONTEXT_MAX_TAGS];

#endif
