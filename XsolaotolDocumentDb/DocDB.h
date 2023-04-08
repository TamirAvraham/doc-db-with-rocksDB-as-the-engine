#pragma once
#include "JsonObject.h"
#include <list>
#include "rocksdb/db.h"
namespace DocDB
{
	class DB;
	class Collection;
	class Document: public http::json::JsonObject {
		friend class DB;
		
	public:
		const std::string getCollectionName();
		const bool updateInDB();
	protected:
		Document(const std::string& name, const std::string& collectionName);
		Document(const std::string& name, const std::string& collectionName, const std::string& value);
		Document(const std::string& name, const std::string& collectionName, const http::json::JsonObject& value);

		std::string _name;
		std::string _collectionName;
	};

	class Collection
	{
	public:


		Collection(const std::string& name,DB& db, rocksdb::ColumnFamilyHandle* handle)noexcept; 
		Collection(const std::string& name,DB& db);
		// getting doc related

		Document getDoc(const std::string& name)const noexcept(false);
		std::list<Document> getAllDocuments() const noexcept;
		int getDocumnetCount()const noexcept;
		bool DoesDocumentExists(const std::string& name)const noexcept;

		// creating doc realted
		Document createDocument(const std::string& name ,const http::json::JsonObject& jsonObject);
		Document createDocument(const std::string& name);
		
	private:	
		DB& _db;
		rocksdb::ColumnFamilyHandle* _columnHandle;
		std::string _name;
	};

	class DB {
	public:
		Collection getCollection(const std::string& collectionName);
		Collection createCollection(const std::string& collectionName);
		bool deleteCollection(const std::string& collectionName);
		
	private:
		friend Collection;
		rocksdb::DB* _db;
		Document getDoc(const rocksdb::ColumnFamilyHandle* handle,const std::string& docName)const noexcept(false);
		void updateDoc(const Document& doc);


		//colection related
		rocksdb::ColumnFamilyHandle* openCollection(const std::string& collectionName) const noexcept(false);

		
		
		
	
	};
}

