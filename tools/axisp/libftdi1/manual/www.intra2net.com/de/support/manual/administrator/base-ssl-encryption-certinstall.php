<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Zertifikate auf Clients installieren | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="base-ssl-encryption.php" title="10. Kapitel - SSL-Verschl&uuml;sselung und Zertifikate"><link rel="prev" href="base-ssl-encryption-config.php" title="10.2. Zertifikate richtig erstellen"><link rel="next" href="base-ssl-encryption-user.php" title="10.4. Benutzer sensibilisieren">
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

<a href="base-ssl-encryption-certinstall.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="base-ssl-encryption-certinstall.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">10.3. Zertifikate auf Clients installieren</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="base-ssl-encryption-config.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">10. Kapitel - SSL-Verschl&uuml;sselung und Zertifikate</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="base-ssl-encryption-user.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="base-ssl-encryption-certinstall"></a>10.3. Zertifikate auf Clients installieren</h2></div></div></div><a class="indexterm" name="base-ssl-encryption-certinstall1"></a><p>Wenn Sie neue Zertifikate selbst erstellt haben, sind sie auf dem Client noch nicht
      bekannt. Die Clientsoftware warnt Sie daher vor einem Schl&uuml;ssel von unbekannter
      Zertifizierungsstelle.</p><p>Bauen Sie die Verbindung auf und installieren Sie das Zertifikat im Client. Bei folgenden
      Sitzungen darf Sie das Programm nicht mehr vor ung&uuml;ltigen Zertifikaten warnen.</p><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-ssl-encryption-certinstall-windows"></a>10.3.1. Installation unter Windows</h3></div></div></div><p>Im Folgenden wird beschrieben, wie Sie das Zertifikat des Intranators in das
        Zertifikatssystem von Windows installieren. Beachten Sie, dass einige Programme (wie z.B.
        Mozilla Firefox) ihr eigenes Zertifikatssystem mitbringen. Sollen solche Programme mit dem
        Intranator genutzt werden, muss das Zertifikat dort zus&auml;tzlich installiert werden. </p><div class="procedure"><ol type="1"><li><p>Starten Sie den Internet Explorer als Administrator. Klicken Sie daf&uuml;r in der
            Startleiste mit Rechts auf den Programmnamen und w&auml;hlen dann <span class="guimenuitem">Als
              Administrator ausf&uuml;hren</span>. Es kann kein anderer Browser verwendet werden
            und es m&uuml;ssen administrative Rechte f&uuml;r das Programm verf&uuml;gbar sein.</p><p>Unter Windows XP und 2003 ist ein Ausf&uuml;hren als Administrator nicht
            notwendig.</p><div class="screenshot"><div class="mediaobject"><img src="../images/base/win-certinstall01.png"></div></div></li><li><p>&Ouml;ffnen Sie die Oberfl&auml;che des Intranator Business Servers per https. Hier im
            Beispiel wird <strong class="userinput"><code>https://intranator.net.lan</code></strong> verwendet. Ersetzen Sie
            dies durch den vollst&auml;ndigen Rechnernamen inkl. Domain Ihres Intranator Business
            Servers.</p><p>Greifen Sie unbedingt &uuml;ber einen DNS-Namen zu, verwenden Sie nicht die IP. Sollte
            der Intranator Business Server nicht per DNS-Namen erreichbar sein, m&uuml;ssen Sie evtl. die
            DNS-Konfiguration anpassen. Dies wird im <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-intranet-dns.php">Abschnitt&nbsp;9.3, &#8222;Domain und DNS&#8220;</a> beschrieben.</p></li><li><p>Der Internet Explorer erkennt die Zertifizierungsstelle des Servers noch nicht als
            vertrauensw&uuml;rdig. Werden zus&auml;tzlich noch andere Zertifikatsprobleme erkannt, muss zuerst
            das Zertifikat des Intranator Business Servers angepasst werden. Dies wird im <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-ssl-encryption.php">10. Kapitel,&nbsp;&#8222;SSL-Verschl&uuml;sselung und Zertifikate&#8220;</a> beschrieben.</p><div class="screenshot"><div class="mediaobject"><img src="../images/base/win-certinstall02.png"></div></div></li><li><p>Klicken Sie auf <span class="guilabel">Laden dieser Webseite fortsetzen (nicht
              empfohlen)</span>.</p></li><li><p>Klicken Sie auf das rote Schild in der URL-Zeile um sich den Sicherheitsbericht
            anzeigen zu lassen.</p><div class="screenshot"><div class="mediaobject"><img src="../images/base/win-certinstall03.png"></div></div></li><li><p>Klicken Sie im Sicherheitsbericht auf <span class="guilabel">Zertifikate
            anzeigen</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/base/win-certinstall04.png"></div></div></li><li><p>Klicken Sie in der Zertifikatsanzeige auf <span class="guibutton">Zertifikat
              installieren</span>. Ist diese Schaltfl&auml;che nicht vorhanden, so fehlen die
            n&ouml;tigen Administrationsrechte.</p><div class="screenshot"><div class="mediaobject"><img src="../images/base/win-certinstall05.png"></div></div></li><li><p>Es &ouml;ffnet sich ein Assistent zum Zertifikatsimport. Lassen Sie das Zertifikat in
            einem ausgew&auml;hlten Speicher speichern und klicken auf
              <span class="guibutton">Durchsuchen...</span> zur Auswahl des Zertifikatsspeichers.</p><div class="screenshot"><div class="mediaobject"><img src="../images/base/win-certinstall06.png"></div></div></li><li><p>W&auml;hlen Sie den Zertifikatsspeicher <span class="guilabel">Vertrauensw&uuml;rdige
              Stammzertifizierungsstellen</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/base/win-certinstall07.png"></div></div></li><li><p>Schlie&szlig;en Sie den Assistent ab. Sie bekommen eine Sicherheitswarnung vom
            Betriebssystem angezeigt. Best&auml;tigen Sie, dass Sie das Zertifikat installieren
            m&ouml;chten.</p><div class="screenshot"><div class="mediaobject"><img src="../images/base/win-certinstall08.png"></div></div></li><li><p>Schlie&szlig;en Sie den Internet Explorer.</p></li><li><p>&Ouml;ffnen Sie den Internet Explorer erneut, diesmal nicht mit Administratorrechten,
            sondern mit normalen Benutzerrechten.</p></li><li><p>&Ouml;ffnen Sie wieder die Oberfl&auml;che des Intranator Business Servers. Diesmal darf keine
            Zertifikatswarnung erscheinen. Neben der URL wird ein Schlosssymbol angezeigt.</p><div class="screenshot"><div class="mediaobject"><img src="../images/base/win-certinstall09.png"></div></div></li></ol></div><p>Sollte es bei der Installation des Zertifikats zu Problemen kommen, finden Sie hier
        einige Punkte, die Sie kontrollieren sollten: </p><div class="itemizedlist"><ul type="disc"><li><p>&Ouml;ffnen Sie im Internet Explorer die <span class="guimenu">Internetoptionen</span>, Reiter
              <span class="guisubmenu">Inhalte</span> und klicken auf <span class="guibutton">Zertifikate</span>.
            Das Zertifikat des Intranators sollte im Reiter <span class="guilabel">Vertrauensw&uuml;rdige
              Stammzertifizierungsstellen</span> enthalten sein.</p><div class="screenshot"><div class="mediaobject"><img src="../images/base/win-certcheck.png"></div></div></li><li><p>Wird das Zertifikat dort nicht angezeigt, suchen Sie, ob es nicht in einem anderen
            Zertifikatsspeicher enthalten ist. Installieren Sie es dann erneut und w&auml;hlen diesmal
              <span class="guilabel">Vertrauensw&uuml;rdige Stammzertifizierungsstellen</span> als Ziel
            aus.</p></li><li><p>Bei einigen Versionen von Windows gibt es einen bekannten Fehler bei den
            Berechtigungen zum Zertifikatsspeicher. Weitere Informationen finden Sie unter <a class="ulink" href="http://support.microsoft.com/kb/932156" target="_top">http://support.microsoft.com/kb/932156</a>.</p></li><li><p>Bei einigen Systemen haben wir im Zusammenhang mit Imaging-Systemen Probleme mit dem
            Eigent&uuml;mer des Zertifikatsspeichers beobachtet. In diesem Falle muss &uuml;ber den
            Registry-Editor der Eigent&uuml;mer dieses Schl&uuml;ssels auf den aktuellen Benutzer umgestellt
            werden:
              <code class="filename">HKCU\Software\Microsoft\SystemCertificates\Root\ProtectedRoots</code>.
            Vergeben Sie danach Leserechte f&uuml;r den Benutzer.</p></li></ul></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-ssl-encryption-certinstall-ad"></a>10.3.2. Verteilen von Zertifikaten &uuml;ber Active Directory</h3></div></div></div><a class="indexterm" name="base-ssl-encryption-certinstall-ad1"></a><a class="indexterm" name="base-ssl-encryption-certinstall-ad2"></a><p>Werden die Client-PCs mit einem Active Directory verwaltet, kann man dieses nutzen um
        das Zertifikat des Intranators an alle zu verteilen.</p><p>Exportieren Sie dazu das verwendete Zertifikat aus dem Intranator &uuml;ber das Men&uuml;
        System&nbsp;&gt;&nbsp;Schl&uuml;ssel&nbsp;&gt;&nbsp;Eigene Schl&uuml;ssel als
        .cer-Datei.</p><p>Befolgen Sie dann die Hinweise von Microsoft zur Verteilung des Zertifikats: <a class="ulink" href="http://technet.microsoft.com/de-de/library/cc758128.aspx" target="_top">http://technet.microsoft.com/de-de/library/cc758128.aspx</a></p><a class="indexterm" name="d0e2055"></a><a class="indexterm" name="d0e2056"></a><a class="indexterm" name="d0e2057"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="base-ssl-encryption-config.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="base-ssl-encryption.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="base-ssl-encryption-user.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">10.2. Zertifikate richtig erstellen&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;10.4. Benutzer sensibilisieren</td></tr></table></div>
      
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