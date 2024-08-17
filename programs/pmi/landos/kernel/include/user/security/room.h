/*
 * File: room.h
 *
 * Descri��o:
 *     Window station. 
 *     Esta��o de janelas. 
 *     (Cont�m desktops).
 *
 *     WINDOW -> DESKTOP -> WINDOW STATION -> USER SECTION.
 *
 * Tipos de window station: 
 *     (interactive, non_interactive).
 *
 * OBS:
 *     Cada PROCESSO est� associado � 
 *     uma window station e s� podem rodar l�.
 *     Uma window station tem v�rios desktops.
 *     Os desktops tem v�rias janelas e menus.
 *
 * History:
 *     2015 - Created by Fred Nora.
 */

#ifndef ____ROOM_H
#define ____ROOM_H    1

 
/*
 * room:
 *     A room os a place to handle a set of desktops.
 *     ( window stations )
 */ 

struct room_d
{
    object_type_t  objectType;
    object_class_t objectClass;

	//object control
	struct object_d *object;
	
    int id;

	int used;
	int magic;
	
	int userID;

    //
    // Desktops
    //

    unsigned long desktop_list[32];


	//struct wstation_d *next_wstation;
	
	//struct desktop_d *arrayDesktop; //ponteiro para um array de estruturas de desktop.
	
	//linked list. ( a linked list da window station)
	struct linkedlist_d *linkedlist;	
	
	//section
    struct room_d *room;
	
	//next
	struct room_d *next;
};
extern struct room_d *room0;
extern struct room_d *CurrentRoom;
//...
extern unsigned long roomList[ROOM_COUNT_MAX];

//
// == prototypes ==================================
//


void set_current_room(struct room_d *room);
void *get_current_room (void);

int RegisterRoom(struct room_d *room);
void *CreateRoom (struct room_d *room);

void init_room_list (void);
void init_room_manager (void);

#endif   

//
// End
//


