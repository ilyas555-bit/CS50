-- MySQL dump 10.14  Distrib 5.5.32-MariaDB, for Linux (i686)
--
-- Host: localhost    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.32-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `ID` int(11) NOT NULL,
  `Transaction` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `time` timestamp(6) NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `Symbol` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `Shares` text COLLATE utf8_unicode_ci NOT NULL,
  `Price` decimal(65,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
INSERT INTO `history` VALUES (13,'BUY','2013-11-07 21:59:48.127293','AAPL','8',512.49),(13,'SELL','2013-11-07 22:00:09.634534','AAPL','28',512.49),(13,'BUY','2013-11-07 22:01:21.699433','AAPL','3',512.49),(13,'BUY','2013-11-07 22:02:21.747540','AAPL','3',512.49),(13,'BUY','2013-11-07 22:02:27.327451','AAPL','8',512.49),(13,'SELL','2013-11-07 22:02:53.026954','AAPL','14',512.49),(13,'BUY','2013-11-07 22:04:13.689124','AAPL','2',512.49),(13,'SELL','2013-11-07 22:04:16.417469','AAPL','2',512.49),(13,'BUY','2013-11-07 22:05:56.240182','AAPL','2',512.49),(13,'SELL','2013-11-07 22:05:59.897194','AAPL','2',512.49),(13,'BUY','2013-11-07 22:15:46.239301','AAPL','2',512.49),(13,'BUY','2013-11-07 22:18:19.747762','GOOG','3',1007.95),(13,'SELL','2013-11-07 22:18:40.669670','AAPL','2',512.49),(13,'SELL','2013-11-07 22:56:42.233497','GOOG','3',1007.95),(13,'BUY','2013-11-07 22:56:46.648690','AAPL','8',512.49),(13,'SELL','2013-11-08 02:50:24.120752','AAPL','8',512.49),(13,'BUY','2013-11-08 02:52:47.318072','GOOG','13',1007.95),(14,'BUY','2013-11-08 03:10:30.913975','AAPL','2',512.49),(14,'BUY','2013-11-08 03:10:37.436657','FB','2',47.56),(14,'SELL','2013-11-08 03:10:41.222287','FB','2',47.56),(15,'BUY','2013-11-08 03:17:33.074003','AAPL','2',512.49),(15,'BUY','2013-11-08 03:17:39.769635','GOOG','1',1007.95),(15,'SELL','2013-11-08 03:18:27.270877','AAPL','2',512.49),(15,'SELL','2013-11-08 03:18:35.674594','GOOG','1',1007.95),(15,'BUY','2013-11-08 03:18:44.337548','AAPL','2',512.49);
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `portfolio`
--

DROP TABLE IF EXISTS `portfolio`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `portfolio` (
  `id` int(10) NOT NULL,
  `symbol` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(100) NOT NULL,
  PRIMARY KEY (`id`,`symbol`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `portfolio`
--

LOCK TABLES `portfolio` WRITE;
/*!40000 ALTER TABLE `portfolio` DISABLE KEYS */;
INSERT INTO `portfolio` VALUES (1,'AAPL',20),(2,'GOOG',3),(3,'INTC',7),(4,'M',10),(5,'YHOO',8),(6,'FB',2),(7,'NKE',9),(8,'TM',6),(13,'GOOG',13),(14,'AAPL',2),(15,'AAPL',2);
/*!40000 ALTER TABLE `portfolio` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `hash` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'caesar','$1$50$GHABNWBNE/o4VL7QjmQ6x0',10000.0000),(2,'hirschhorn','$1$50$lJS9HiGK6sphej8c4bnbX.',10000.0000),(3,'jharvard','$1$50$RX3wnAMNrGIbgzbRYrxM1/',10000.0000),(4,'malan','$1$HA$azTGIMVlmPi9W9Y12cYSj/',10000.0000),(5,'milo','$1$HA$6DHumQaK4GhpX8QE23C8V1',10000.0000),(6,'skroob','$1$50$euBi4ugiJmbpIbvTTfmfI.',10000.0000),(7,'zamyla','$1$50$uwfqB45ANW.9.6qaQ.DcF.',10000.0000),(13,'Lily','$1$xacg1.uG$9XDQVF5MZtLjboS8WZar9.',14022.3340),(14,'yolo','$1$p4K/FVnU$G4Iq9zfg4C1Pd260bS04q.',8975.0160),(15,'lolol','$1$26bcR26W$wJW2Z2Tj0xL0YcLRZ.zZs1',18975.0160);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-11-07 22:33:59
