<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Backup | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="base-system.php" title="17. Kapitel - Systemfunktionen"><link rel="prev" href="base-system-updates.php" title="17.2. Updates"><link rel="next" href="base-system-behind-firewall.php" title="17.4. Betrieb hinter einer Firewall">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="base-system-backup.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="base-system-backup.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">17.3. Backup</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="base-system-updates.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">17. Kapitel - Systemfunktionen</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="base-system-behind-firewall.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="base-system-backup"></a>17.3. Backup</h2></div></div></div><a class="indexterm" name="base-system-backup1"></a><p>Der Intranator enth&auml;lt au&szlig;er den Konfigurationsdaten bei Verwendung von IMAP auch alle
      E-Mails. Daher ist ein regelm&auml;&szlig;iges Backup umso wichtiger.</p><p>Der Intranator beginnt in der Standardkonfiguration t&auml;glich um 02:00 Uhr mit dem Sichern
      aller Daten. Zus&auml;tzlich kann unter System&nbsp;&gt;&nbsp;Backup&nbsp;&gt;&nbsp;Einstellungen
      ein Backup auch manuell angesto&szlig;en werden.</p><p>Zur Sicherung der Backups kann entweder der Zugriff auf einen Rechner oder Benutzer
      beschr&auml;nkt werden oder die Backups zus&auml;tzlich per GnuPG verschl&uuml;sselt werden. Im
      Auslieferungszustand werden die Backups aus Sicherheitsgr&uuml;nden auf einen Benutzer mit einem
      per Zufallsgenerator erzeugten Passwort beschr&auml;nkt. &Auml;ndern Sie dieses Passwort oder sch&uuml;tzen
      Sie Ihre Backups mit einer anderen Methode.</p><a class="indexterm" name="d0e5117"></a><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-system-backup-remote"></a>17.3.1. Auslagern</h3></div></div></div><a class="indexterm" name="base-system-backup-remote1"></a><p>Bei einem Backup werden die Daten in 650 MB gro&szlig;en Dateibl&ouml;cken auf die Festplatte
        geschrieben. Es bleiben immer 2 Backups&auml;tze auf dem Intranator. Selbstverst&auml;ndlich reicht es
        nicht aus, das Backup in eine Datei auf dem Intranator zu sichern, da z.B. die Festplatte
        kaputt gehen k&ouml;nnte.</p><p>Deshalb k&ouml;nnen die Backups&auml;tze per HTTP oder SMB/CIFS (Windows Freigabe) vom Intranator
        auf einen anderen Rechner heruntergeladen werden. Dies kann z.B. durch eine automatisch
        gestartete Batchdatei geschehen oder indem das Verzeichnis auf dem Intranator einfach in ein
        bestehendes Backupprogramm mit aufgenommen wird.</p><p>Eine andere M&ouml;glichkeit ist das automatische entfernte Ablegen. Ist diese Funktion
        aktiv, l&auml;dt der Intranator die Backupdateien automatisch auf einen Zielserver hoch sobald
        sie erstellt wurden. Dies kann &uuml;ber das FTP- oder SMB-Protokoll geschehen. Per SMB kann der
        Intranator auch automatisch alte Backups&auml;tze l&ouml;schen.</p><a class="indexterm" name="d0e5132"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-system-backup-restore"></a>17.3.2. R&uuml;cksichern</h3></div></div></div><a class="indexterm" name="base-system-backup-restore1"></a><p>Zum R&uuml;ckspielen von Backups k&ouml;nnen Backups&auml;tze per SMB/CIFS auf den Intranator
        hochgeladen werden. Unter System&nbsp;&gt;&nbsp;Backup&nbsp;&gt;&nbsp;Wiederherstellen kann
        das R&uuml;ckspielen gestartet werden.</p><p>Es gibt verschiedene M&ouml;glichkeiten Backups zur&uuml;ckzuspielen: Komplett (Konfiguration und
        E-Mails), nur die Konfiguration (alle E-Mails werden dabei gel&ouml;scht!) oder nur die E-Mails
        eines Benutzers.</p><p>Die E-Mails eines Benutzers k&ouml;nnen auch in einen IMAP Unterorder eines Benutzers
        zur&uuml;ckgespielt werden. Wurden z.B. einzelne wichtige E-Mails aus Versehen gel&ouml;scht, so
        k&ouml;nnen Sie damit zur&uuml;ckgeholt werden, ohne dass neuere E-Mails &uuml;berschrieben werden. </p><a class="indexterm" name="base-system-backup-restore-version"></a><p>Der Intranator kann Backups von alten Versionen zur&uuml;ckspielen. Dabei durchl&auml;uft die
        Konfiguration des Backups intern den Updateprozess. Es ist aber nicht m&ouml;glich, Backups von
        neueren Versionen zur&uuml;ckzuspielen.</p><a class="indexterm" name="d0e5154"></a><a class="indexterm" name="d0e5155"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-system-backup-restore-procedure"></a>17.3.3. Vorgehen bei Festplattenschaden oder Hardwaretausch</h3></div></div></div><a class="indexterm" name="base-system-backup-restore-procedure1"></a><a class="indexterm" name="base-system-backup-restore-procedure2"></a><p>Nach einem Festplattenschaden oder beim Tausch der f&uuml;r den Intranator verwendeten
        Hardware empfehlen wir nach der folgenden Liste vorzugehen. Wir raten dringend davon ab, die
        Daten des Intranators &uuml;ber Festplatten-Imaging-Programme oder &auml;hnliche L&ouml;sungen zu
        transferieren. Bei einem Festplattendefekt w&uuml;rden die Defekte einfach mitkopiert, bei neuer
        Hardware bereiten h&auml;ufig auch nur minimale Differenzen in der Festplattengr&ouml;&szlig;e Probleme mit
        dem Dateisystem.</p><div class="orderedlist"><p class="title"><b>Bei Hardwareumzug</b></p><ol type="1"><li><p>Deaktivieren Sie das E-Mail- und Groupwaresystem im Men&uuml;
            Dienste&nbsp;&gt;&nbsp;E-Mail&nbsp;&gt;&nbsp;Einstellungen damit keine neu ankommenden
            E-Mails verloren gehen k&ouml;nnen</p></li><li><p>Backup starten</p></li><li><p>Wenn E-Mail-Archivierung in Verwendung: Kontrollieren ob die
            Archivierungsschnittstelle vollst&auml;ndig abgerufen und geleert wurde</p></li><li><p>Fertiges Backup auf anderen Rechner kopieren</p></li></ol></div><div class="orderedlist"><p class="title"><b>Bei Defekt und Hardwareumzug</b></p><ol start="5" type="1"><li><p>Aktuelle Installations-CD f&uuml;r den Intranator von <a class="ulink" href="../../../../index.html" target="_top">www.intra2net.com</a> herunterladen und auf CD
            brennen</p></li><li><p>Von der Installations-CD starten und Intranator installieren</p></li><li><p>Tragen Sie in der Installations-Maske den IP-Bereich Ihres lokalen Netzes ein</p></li><li><p>Verf&uuml;gt die neue Hardware &uuml;ber 2 Festplatten, aktivieren Sie jetzt &uuml;ber die
            Weboberfl&auml;che, Men&uuml; System&nbsp;&gt;&nbsp;Hardware&nbsp;&gt;&nbsp;RAID, die
            Festplattenspiegelung</p></li><li><p>&Ouml;ffnen Sie die Weboberfl&auml;che des Intranators und setzen ein neues Passwort f&uuml;r die
            Backup-Freigabe (Men&uuml; System&nbsp;&gt;&nbsp;Backup&nbsp;&gt;&nbsp;Einstellungen)</p></li><li><p>Kopieren Sie das Backup vom anderen Rechner auf die Restore-Freigabe des
            Intranators</p></li><li><p>Spielen Sie das Backup mit Konfiguration und E-Mails auf den Intranator
            zur&uuml;ck</p></li><li><p>Aktivieren Sie das E-Mail- und Groupwaresystem wieder, sofern Sie dieses vorher deaktiviert
            hatten</p></li><li><p>Konfiguration, E-Mails und Statistikdaten sind wiederhergestellt und funktionsf&auml;hig
            wie vorher</p></li></ol></div><a class="indexterm" name="d0e5217"></a><a class="indexterm" name="d0e5218"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="base-system-updates.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="base-system.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="base-system-behind-firewall.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">17.2. Updates&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;17.4. Betrieb hinter einer Firewall</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>