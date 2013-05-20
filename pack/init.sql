/*
Navicat SQLite Data Transfer

Source Server         : w_db
Source Server Version : 30706
Source Host           : :0

Target Server Type    : SQLite
Target Server Version : 30706
File Encoding         : 65001

Date: 2013-05-20 15:21:08
*/

PRAGMA foreign_keys = OFF;

-- ----------------------------
-- Table structure for "main"."tab_admin"
-- ----------------------------
DROP TABLE "main"."tab_admin";
CREATE TABLE "tab_admin" (
"id"  VARCHAR(48) NOT NULL,
"admin_name"  VARCHAR(20) NOT NULL,
"admin_pass"  VARCHAR(20) NOT NULL,
"create_by"  VARCHAR(48) NOT NULL,
"create_time"  DATE NOT NULL,
"del_flag"  SMALLINT NOT NULL,
PRIMARY KEY ("id" ASC)
);

-- ----------------------------
-- Records of tab_admin
-- ----------------------------
INSERT INTO "main"."tab_admin" VALUES ('{E9E41B9C-0176-4119-8BBB-ACC5F0C086D4}', 'admin', 123456, '{E9E41B9C-0176-4119-8BBB-ACC5F0C086D4}', '2013-03-12 10:41:10', 0);

-- ----------------------------
-- Table structure for "main"."tab_check"
-- ----------------------------
DROP TABLE "main"."tab_check";
CREATE TABLE "tab_check" (
"id"  VARCHAR(48) NOT NULL,
"u_id"  VARCHAR(48) NOT NULL,
"m_id"  VARCHAR(48) NOT NULL,
"c_id"  VARCHAR(48) NOT NULL,
"w_id"  VARCHAR(48) NOT NULL,
"modal"  INTEGER NOT NULL,
"num"  INTEGER NOT NULL,
"total"  DOUBLE NOT NULL,
"tellphone"  VARCHAR(20) NOT NULL,
"detail"  TEXT NOT NULL,
"create_by"  VARCHAR(48) NOT NULL,
"create_time"  DATE NOT NULL,
"del_flag"  SMALLINT NOT NULL,
PRIMARY KEY ("id" ASC)
);

-- ----------------------------
-- Records of tab_check
-- ----------------------------

-- ----------------------------
-- Table structure for "main"."tab_class"
-- ----------------------------
DROP TABLE "main"."tab_class";
CREATE TABLE "tab_class" (
"id"  VARCHAR(48) NOT NULL,
"class_name"  VARCHAR(100) NOT NULL,
"p_name"  VARCHAR(20) NOT NULL,
"c_name"  VARCHAR(20) NOT NULL,
"people_num"  INTEGER NOT NULL,
"tellphone"  VARCHAR(20) NOT NULL,
"detail"  TEXT NOT NULL,
"create_by"  VARCHAR(48) NOT NULL,
"create_time"  DATE NOT NULL,
"del_flag"  SMALLINT NOT NULL,
PRIMARY KEY ("id")
);

-- ----------------------------
-- Records of tab_class
-- ----------------------------

-- ----------------------------
-- Table structure for "main"."tab_company"
-- ----------------------------
DROP TABLE "main"."tab_company";
CREATE TABLE "tab_company" (
"id"  VARCHAR(48) NOT NULL,
"am_id"  VARCHAR(48) NOT NULL,
"company_name"  VARCHAR(48) NOT NULL,
"compant_address"  VARCHAR(100) NOT NULL,
"company_tellphone"  VARCHAR(20) NOT NULL,
"company_contact"  VARCHAR(20) NOT NULL,
"detail"  TEXT NOT NULL,
"create_by"  VARCHAR(48) NOT NULL,
"create_time"  DATE NOT NULL,
"del_flag"  SMALLINT NOT NULL,
PRIMARY KEY ("id")
);

-- ----------------------------
-- Records of tab_company
-- ----------------------------

-- ----------------------------
-- Table structure for "main"."tab_material"
-- ----------------------------
DROP TABLE "main"."tab_material";
CREATE TABLE "tab_material" (
"id"  VARCHAR(48) NOT NULL,
"material_name"  VARCHAR(48) NOT NULL,
"material_modal"  VARCHAR(48) NOT NULL,
"material_manuf"  VARCHAR(100) NOT NULL,
"material_unit"  VARCHAR(48) NOT NULL,
"material_price"  DOUBLE NOT NULL,
"material_total"  INTEGER NOT NULL,
"detail"  TEXT NOT NULL,
"create_by"  VARCHAR(48) NOT NULL,
"create_time"  DATE NOT NULL,
"del_flag"  SMALLINT NOT NULL,
PRIMARY KEY ("id" ASC)
);

-- ----------------------------
-- Records of tab_material
-- ----------------------------

-- ----------------------------
-- Table structure for "main"."tab_user"
-- ----------------------------
DROP TABLE "main"."tab_user";
CREATE TABLE "tab_user" (
"id"  VARCHAR(48) NOT NULL,
"am_id"  VARCHAR(48) NOT NULL,
"user_name"  VARCHAR(48) NOT NULL,
"user_company"  VARCHAR(48) NOT NULL,
"user_age"  INTEGER NOT NULL,
"user_tellphone"  VARCHAR(20) NOT NULL,
"user_email"  VARCHAR(100) NOT NULL,
"detail"  TEXT NOT NULL,
"create_by"  VARCHAR(48) NOT NULL,
"create_time"  DATE NOT NULL,
"del_flag"  SMALLINT NOT NULL,
PRIMARY KEY ("id")
);

-- ----------------------------
-- Records of tab_user
-- ----------------------------

-- ----------------------------
-- Table structure for "main"."tab_warehouse"
-- ----------------------------
DROP TABLE "main"."tab_warehouse";
CREATE TABLE "tab_warehouse" (
"id"  VARCHAR(48) NOT NULL,
"company_name"  VARCHAR(48) NOT NULL,
"admin_name"  VARCHAR(48) NOT NULL,
"warehouse_name"  VARCHAR(48) NOT NULL,
"admin_tellphone"  VARCHAR(20) NOT NULL,
"admin_email"  VARCHAR(100) NOT NULL,
"detail"  TEXT NOT NULL,
"create_by"  VARCHAR(48) NOT NULL,
"create_time"  DATE NOT NULL,
"del_flag"  SMALLINT NOT NULL,
PRIMARY KEY ("id")
);

-- ----------------------------
-- Records of tab_warehouse
-- ----------------------------
