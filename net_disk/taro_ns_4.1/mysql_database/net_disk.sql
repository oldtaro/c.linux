-- MySQL dump 10.13  Distrib 8.0.28, for Linux (x86_64)
--
-- Host: localhost    Database: net_disk
-- ------------------------------------------------------
-- Server version	8.0.28

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `file_info`
--

DROP TABLE IF EXISTS `file_info`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `file_info` (
  `code` int NOT NULL AUTO_INCREMENT,
  `precode` int DEFAULT NULL,
  `type` varchar(1) DEFAULT NULL,
  `usr_id` int DEFAULT NULL,
  `file_name` varchar(50) DEFAULT NULL,
  `file_size` int DEFAULT NULL,
  `md5` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`code`)
) ENGINE=InnoDB AUTO_INCREMENT=27 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `file_info`
--

LOCK TABLES `file_info` WRITE;
/*!40000 ALTER TABLE `file_info` DISABLE KEYS */;
INSERT INTO `file_info` VALUES (23,0,'d',5,'dir1',4096,'(null)'),(24,0,'d',5,'dir2',4096,'(null)'),(25,23,'d',5,'dir3',4096,'(null)'),(26,23,'f',5,'test',58607115,'a87abf2b21b816f3c8f0eb950f94cc94');
/*!40000 ALTER TABLE `file_info` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `file_pool`
--

DROP TABLE IF EXISTS `file_pool`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `file_pool` (
  `code` int NOT NULL AUTO_INCREMENT,
  `index_count` int DEFAULT NULL,
  `file_size` int DEFAULT NULL,
  `md5` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`code`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `file_pool`
--

LOCK TABLES `file_pool` WRITE;
/*!40000 ALTER TABLE `file_pool` DISABLE KEYS */;
INSERT INTO `file_pool` VALUES (10,1,58607115,'a87abf2b21b816f3c8f0eb950f94cc94');
/*!40000 ALTER TABLE `file_pool` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `usr_info`
--

DROP TABLE IF EXISTS `usr_info`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `usr_info` (
  `id` int NOT NULL AUTO_INCREMENT,
  `usr_name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `salt` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `usr_pwd` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `usr_info`
--

LOCK TABLES `usr_info` WRITE;
/*!40000 ALTER TABLE `usr_info` DISABLE KEYS */;
INSERT INTO `usr_info` VALUES (5,'lzy','$6$vTf92fG5$V','$6$vTf92fG5$kEIzqQovcylwnlYCLdIlXcxylX7VXKTc1NqBzPXjhvfKQ8xzsQ8/XrSzS/1kqAVmfr1Z5w/aEBe9Bl8bW0mSF0'),(6,'taro','$6$Au4K70d0','$6$Au4K70d0$MzPu3zXUNOA5TLDGnkn/uUGyLCAFs9lNmH/8oVPleLkwLoP1.sBMJ769dqkCykkFd2LGQG1h0WJFCcZcF/49j1'),(8,'lilei','$6$YN05e9g3','$6$YN05e9g3$Ilhzm8aPbHn22iRGfEk5ohmI5AeMQH6X.GG9lxOy9PVhvAQ/0l8JpS6Nd2TzDyHJYdN.bBu0pA5ABjKt5V1ht/');
/*!40000 ALTER TABLE `usr_info` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-02-28 13:28:51
