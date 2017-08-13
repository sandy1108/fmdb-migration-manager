//
//  FmdbMigrationManager.h
//  FmdbMigrationManager
//
//  Created by Dr Nic Williams on 2008-09-06.
//  Copyright 2008 Mocra and Dr Nic Williams. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FMDatabase.h"

@interface FmdbMigrationManager : NSObject {
	FMDatabase *db_;
	NSArray *migrations_;
	NSInteger currentVersion_;
	NSString *schemaMigrationsTableName_;
}
@property (retain) FMDatabase *db;
@property (retain) NSArray *migrations;
@property (assign,readonly) NSInteger currentVersion;
@property (readonly) NSString *schemaMigrationsTableName;

/**
 按照数组中的migration对象，对指定数据库依次执行数据库升级操作。
 
 @param aPath 数据库文件路径
 @param migrations migration对象的数组，其中，第n个元素为数据库n版本升级为n+1版本使用的对象(n从0开始)
 */
+ (id)executeForDatabasePath:(NSString *)aPath withMigrations:(NSArray *)migrations;

- (id)initWithDatabasePath:(NSString *)aPath;
- (void)executeMigrations;

#pragma mark -
#pragma mark Internal methods

- (void)initializeSchemaMigrationsTable;
- (void)performMigrations;
- (void)recordVersionStateAfterMigrating:(NSInteger)version;

#pragma mark -
#pragma mark Migration up to a defined version

/**
 按照数组中的migration对象，对指定的数据库进行版本和数据库结构升级或降级到指定版本的操作。
 
 @param aPath 数据库文件路径
 @param migrations migration对象的数组，其中，第n个元素为数据库n版本与n+1版本之间升级与降级操作的对象(n从0开始)
 @param aVersion 需要将数据库升级到的指定版本号。如果指定版本号比本地数据库低，会进行降级到指定版本操作。
 */
+ (id)executeForDatabasePath:(NSString *)aPath withMigrations:(NSArray *)migrations andMatchVersion:(NSInteger)aVersion;
- (void)executeMigrationsAndMatchVersion:(NSInteger)aVersion;
- (void)performMigrationsAndMatchVersion:(NSInteger)aVersion;
@end
