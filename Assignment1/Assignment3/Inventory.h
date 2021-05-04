#pragma once

#include <iostream>
#include "Item.h"

class Inventory
{
public:

	//COMMENT: Use more often the initialization list for constructors.
	Inventory() 
	{
		//TODO: Implement a default constructor for the Inventory class where the max number of slots
		// is 5 and all the slots are free (They are not occupied).
		mMaxSlots = 5;
		mSlotsOccupied = 0;
		mInventory = new Item[mMaxSlots];
	}

	//COMMENT: Use more often the initialization list for constructors.
	Inventory(uint32_t capacity)
	{
		//TODO: Implement a non default constructor for the Inventory class where 
		//all the slots are free (They are not occupied).
		mMaxSlots = capacity;
		mSlotsOccupied = 0;
		mInventory = new Item[capacity];
		
	}

	//ERROR: -10. This is not how you create a copy constructor. You should copy all the elements 
	//of other.
	Inventory(const Inventory& other)
		:mMaxSlots(other.mMaxSlots), mSlotsOccupied(other.mSlotsOccupied)
	{
		//TODO: Implement a copy constructor for this class. Avoid shallow copy.
	
		mInventory = other.mInventory;

	}

	
	Inventory(Inventory&& other)
		:mMaxSlots(other.mMaxSlots), mSlotsOccupied(other.mSlotsOccupied)
	{
		//TODO: Implement a move constructor for this class. Reset to a default state the other inventory.
			//copy elements in the inventory
		
			mInventory = other.mInventory;


		other.mMaxSlots = 5;
		other.mSlotsOccupied = 0;
		//delete[] other.mInventory;
	}

	//ERROR: -10. You are allocating memory, so you should delete.
	~Inventory() 
	{
		//TODO: Implement a destructor for this class.
		//delete[] mInventory;
	}

	//ERROR: -10. This is not how you create a copy assignment operator. You should copy all the elements 
	//of other.
	//TODO: Implement a copy assignment operator
	Inventory& operator = (const Inventory& other) {
		if (this != &other) {
			mMaxSlots = other.mMaxSlots;
			mSlotsOccupied = other.mSlotsOccupied;

			delete[] mInventory;
			mInventory = nullptr;

			mInventory = new Item;

			
			mInventory = other.mInventory;


		}
		return *this;
	 }
	//TODO: Implement a move assignment operator
	Inventory& operator=(Inventory&& other) {
		if (this != &other) {
			mMaxSlots = other.mMaxSlots;
			other.mMaxSlots = 0;

			mSlotsOccupied = other.mSlotsOccupied;
			other.mSlotsOccupied = 0;
			
			delete[] mInventory;
			mInventory = nullptr;

			mInventory = other.mInventory;
			other.mInventory = nullptr; 
		}

	}



	//ERROR: -2. Sorry, it was all good, until you created an hp Item inside this function...
	//Follow the correct code for your review.
	void AddItem(Item newItem)
	{
		if (!isFullForItem(&newItem))
		{
			int slotIndex = SearchItemByNameLessThan50(newItem.name);
			//I have this Item in inventory
			if (slotIndex != -1)
			{
				int futureQuantity = mInventory[slotIndex].quantity + newItem.quantity;
				if (futureQuantity > 50)
				{
					newItem.quantity = futureQuantity - 50;
					mInventory[slotIndex].quantity = 50;
					mInventory[mSlotsOccupied] = newItem;
					mSlotsOccupied++;
					return;
				}

				mInventory[slotIndex].quantity += newItem.quantity;
				return;
			}
			//Inserting for the first time
			else
			{
				//Expanding inventory;
				if ((newItem.type == ItemType::Charm) && (newItem.name.compare("Expansion") == 0))
				{
					Item* temp = mInventory;
					mMaxSlots += 5;
					mInventory = new Item[mMaxSlots];
					for (int i = 0; i < mSlotsOccupied; ++i)
					{
						mInventory[i] = temp[i];
					}
					delete[] temp;
					temp = nullptr;
				}

				//After expansion, insert.
				mInventory[mSlotsOccupied] = newItem;
				mSlotsOccupied++;
			}
		}

		std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
	}


	//void AddItem(Item newItem) 
	//{

	//	//TODO: Implement AddItem MethodThis method adds a new item to the inventory. 
	//	//First it searches for this item to see if the item exists, and if the item exists 
	//	//it checks the quantity, because the max quantity allowed per slot is 50.
	//	//So, for example, if you have 50 healing potions in your inventory, and you want to add one more, this potion
	//	//should occupy a new slot. Pay attention that the SearchItem function already does this quantity check for you.
	//	//The extra check that you should do is for the accumulated quantity. So your function should check
	//	//how many items this current slot has and if you add this new item quantity, how many items you will have.
	//	//If it's greater than 50, you should make the quantity of one slot 50 and add the remainder quantity to a new slot.
	//	//For example:
	//	//[ HP 48 ] [  ] [  ] [  ] [  ] Inventory has a HP(healing potions) with 48 as quantity and you want to add more 5 HP
	//	//[ HP 50 ] [HP 3] [  ] [  ] [  ] Inventory after you added 5 HP
	//	
	//	//If the Inventory is full, return a message to the user that the inventory is full and the items will be discarted.
	//	//Use the method IsFullForItem;

	//	//If after you insert the item your inventory becomes full for the remainder, Print a message to the user with how many
	//	//items will be discarted;

	//	//SPECIAL CASE: If the user adds an item of type charm with the name "Expansion" your inventory
	//	//should expand adding 5 more empty slots for the user.
	//	if (newItem.name == "Expansion") {
	//		mMaxSlots += 5;
	//	}
	//	else {
	//		if (mSlotsOccupied < mMaxSlots) {
	//			int index = SearchItemByName(newItem.name);
	//			int notFullIndex = SearchItemByNameLessThan50(newItem.name);
	//			int amountToFulfill = 0;
	//			int total = 0;
	//			if (index != -1) {
	//				//item found
	//				std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
	//				//check for item that is not full
	//				if (notFullIndex != -1) {
	//					//add the amount requested untill reaching 50
	//					//iff  the summ of both is greater that 50 take the rest into a new slot item
	//					total = mInventory[notFullIndex].quantity + newItem.quantity;
	//					if (total < 50) {
	//						Item x = mInventory[index];
	//						mInventory[index].quantity += newItem.quantity;
	//					}
	//					else {
	//						//calculate the remainder after adding to the slot
	//						amountToFulfill = 50 - mInventory[index].quantity;

	//						mInventory[index].quantity += amountToFulfill;
	//						total = newItem.quantity - amountToFulfill;
	//						//call the function again passing a new item with the remainding quantity
	//						Item hps{ newItem.name, total, newItem.type }; //What???
	//						++mSlotsOccupied;
	//						AddItem(hps);
	//					}
	//				}
	//				else {
	//					//check if quantity is more than 50 
	//					total = mInventory[index].quantity += newItem.quantity;
	//					if (newItem.quantity < 50) {
	//						//create a new slot fo item with 50 quantity
	//						++mSlotsOccupied;
	//						mInventory[mSlotsOccupied] = newItem;
	//					}
	//					else {
	//						total = newItem.quantity - 50;
	//						Item hps{ newItem.name, total, newItem.type };//What?????
	//						++mSlotsOccupied;
	//						AddItem(hps);
	//					}

	//				}
	//			}
	//			else {
	//				//check if quantity is more than 50 
	//				if (total < 50) {
	//					Item n = mInventory[mSlotsOccupied];
	//					mInventory[mSlotsOccupied-1]= newItem;
	//					int x = sizeof(mInventory);
	//					++mSlotsOccupied;
	//					std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
	//				}
	//				else {
	//					//create a new slot fo item with 50 quantity
	//					total = newItem.quantity - 50;
	//					Item hps{ newItem.name, total, newItem.type };
	//					++mSlotsOccupied;
	//					std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
	//					AddItem(hps);
	//				}
	//			}

	//		}
	//		else {
	//			std::cout << "inventory full, items will be discarted: " << newItem.quantity << " " << newItem.name << "\n";
	//		}
	//	}
	//	
	//	

	//}

 	void RemoveItem(std::string itemName, int quantity) 
	{
		//TODO: Implement RemoveItem method
		//RemoveItem, should remove a quantity from the slot with the item. If the whole slot 
		//is empty, you should shift all the other items of the inventory;
		//If you try to remove more than what you have in one slot, just make the slot empty.
		//For example:
		//[ HP 50 ] [ HP 30 ] [  ] [  ] [  ] //You tried to remove 80 HP from the inventory
		//[ HP 30 ] [  ] [  ] [  ] [  ] //You just remove from one slot.
		
		int index = SearchItemByName(itemName);
		//find item by name
		int x = mInventory[index].quantity;
		if (SearchItemByName(itemName) != -1) {
			std::cout << "Removing " << quantity << " " << itemName << " from inventory." << "\n";

			//search the item that is not full
			int indexofItem = SearchItemByNameLessThan50(itemName);
			
			if (indexofItem != -1) {
				if (quantity > mInventory[indexofItem].quantity) {
					//reduce the quantity according to iteam quantity
					
					quantity -= mInventory[indexofItem].quantity;
					//re assign items
					moveItemsInInventory(indexofItem);
					//call function again with the new parameters
					RemoveItem(itemName, quantity);
				}
				else {
					int y = mInventory[indexofItem].quantity - quantity;
					mInventory[indexofItem].quantity -= quantity;
				}	
			}
			else {
				// check if quantity is bigger than block
				if (quantity > mInventory[index].quantity) {
					//reduce the quantity according to iteam quantity
					quantity -= mInventory[index].quantity;

					//re assign items
					moveItemsInInventory(index);
					//call function again with the new parameters
					RemoveItem(itemName, quantity);

				}
				else {
					int y = mInventory[index].quantity;
					mInventory[index].quantity -= quantity;
				}
			}
			
		}
		else {
			//print no potion exist
			std::cout << "no item : " << itemName << " found from inventory." << "\n";
		}
		
		//SPECIAL CASE: If the user removes the charm Expansion from the inventory, your inventory 
		//should reduce the number of slots in 5, discarting all the items from the removed slots.
	}
	
	//move the items accoriding to the index wich was removed
	//shouldnt it be better to use linked lists for this problems? *question
	void moveItemsInInventory(int index) {
		for (int x = index; x < mSlotsOccupied; x++) {
			//move the next item to position of the removed one
			mInventory[x] = mInventory[x + 1];
		}
		//reduce slots occupied
		mSlotsOccupied -= 1;
	}

	Item* UseItem(std::string itemName) 
	{
		// TODO: Search for the item and if it exists, return this item and remove one from the inventory
		
		int index = SearchItemByName(itemName);
		//find item by name
		if (SearchItemByName(itemName) != -1) {
			//search the item that is not full
			int indexofItem = SearchItemByNameLessThan50(itemName);
			if (indexofItem != -1) {
				mInventory[indexofItem].quantity -= 1;
				//monve inventory
				if (mInventory[indexofItem].quantity == 0) {
					moveItemsInInventory(indexofItem);
				}
			}else{
				mInventory[index].quantity -= 1;
				//monve inventory
				if (mInventory[indexofItem].quantity == 0) {
					moveItemsInInventory(index);
				}
			}
			std::cout << "Using " << itemName << "\n";
		}
		else {
			std::cout << "iten: " << itemName << "not foung" << "\n";
		}

		// otherwise, return nullptr.
		// The user is just allowed to use the Types: Posion and Utility.
		
	}
private:
	//Array of Items
	Item* mInventory;

	//This variable tracks the capacity of the inventory
	uint32_t mMaxSlots;
	//This variable tracks how many slots are occupied.
	uint32_t mSlotsOccupied;


	//This method seaches for the item inside the Inventory and if it finds the item with less than
	//50 as quantity, it returns the index of the item inside the inventory array, otherwise, returns -1.
	int SearchItemByNameLessThan50(std::string target) const
	{
		int index = -1;
		for (int i = 0; i < mSlotsOccupied; i++)
		{
			if (target.compare(mInventory[i].name) == 0 && mInventory[i].quantity < 50)
			{
				index = i;
				break;
			}
		}

		return index;
	}

	//Returns the index of the item if it exists and -1 if it doesn't.
	int SearchItemByName(std::string target) const 
	{
		int index = -1;
		for (int i = 0; i < mSlotsOccupied; i++)
		{
			if (target.compare(mInventory[i].name) == 0)
			{
				index = i;
				break;
			}
		}
		return index;
	}

	//If you don't have the item inside the inventory and all the slots are occupied - True
	//If you have the item in the inventory with max capacity and all the other slots are occupied - True
	//Otherwise - False.
	bool isFullForItem(Item* item) const
	{
		int index = SearchItemByNameLessThan50((*item).name);
		if (index == -1 && mSlotsOccupied == mMaxSlots)
		{
			return true;
		}
		if (index != -1 && mInventory[index].quantity >= 50 && mSlotsOccupied == mMaxSlots) 
		{
			return true;
		}
		return false;
	}
};