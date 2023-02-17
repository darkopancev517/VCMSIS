<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>ActiveSync mit Android-Ger&auml;ten | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="webgroupware.php" title="Teil&nbsp;4.&nbsp;Web-Groupware und ActiveSync"><link rel="prev" href="webgroupware-activesync-tips.php" title="29.3. Besonderheiten und Tipps"><link rel="next" href="webgroupware-activesync-ios.php" title="31. Kapitel - ActiveSync mit Apple iOS-Ger&auml;ten">
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

<a href="webgroupware-activesync-android.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="webgroupware-activesync-android.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">30. Kapitel - ActiveSync mit Android-Ger&auml;ten</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="webgroupware-activesync-tips.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">Teil&nbsp;4.&nbsp;Web-Groupware und ActiveSync</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="webgroupware-activesync-ios.php">Weiter</a></td></tr></table><hr></div><div class="chapter" lang="de"><div class="titlepage"><div><div><h2 class="title"><a name="webgroupware-activesync-android"></a>30. Kapitel - ActiveSync mit Android-Ger&auml;ten</h2></div></div></div><p>Bevor Sie das Ger&auml;t konfigurieren k&ouml;nnen, m&uuml;ssen Sie den Intranator Server f&uuml;r die
        Anbindung vorbereiten. F&uuml;hren Sie dazu die in <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="webgroupware-activesync-serverconfig.php">Abschnitt&nbsp;29.2, &#8222;Einstellungen auf dem Server&#8220;</a> beschriebenen Schritte durch.</p><p>Haben Sie sich entschlossen, auf dem Intranator Server kein Zertifikat einer offiziellen
        Zertifizierungsstelle, sondern ein selbsterstelltes, einzusetzen, muss das Android-Ger&auml;t f&uuml;r
        den Zeitraum der Konfiguration &uuml;ber eine vertrauensw&uuml;rdige Verbindung direkt mit dem
        Intranator verbunden sein. Hierf&uuml;r kommt ein direkt an den Intranator angeschlossener und
        per WPA2 gesch&uuml;tzter WLAN-Accesspoint oder eine VPN-Verbindung mit dem Intranator in
        Betracht.</p><p>Eine UMTS-Verbindung oder ein nicht direkt lokal am Intranator angeschlossenes WLAN sind
        ungeeignet. Wollen Sie diese Verbindungsarten zur Konfiguration nutzen, muss ein Zertifikat
        einer offiziellen Zertifizierungsstelle verwendet werden.</p><p>Gehen Sie zur Konfiguration wie folgt vor:</p><div class="procedure"><ol type="1"><li><p>Haben Sie sich entschlossen, auf dem Intranator Server kein Zertifikat einer
                offiziellen Zertifizierungsstelle, sondern ein selbsterstelltes, einzusetzen,
                verifizieren Sie als erstes, dass die Internetverbindung &uuml;ber den Mobilfunkprovider
                (UMTS bzw. LTE) dauerhaft deaktiviert ist.</p></li><li><p>Stellen Sie als n&auml;chstes sicher, dass die Zugangsdaten vertraulich bleiben. Die
                daf&uuml;r n&ouml;tigen Schritte werden in <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="vpn-android-galaxys4.php#vpn-android-prepare">Abschnitt&nbsp;46.1, &#8222;Ger&auml;t vorbereiten&#8220;</a> beschrieben.</p></li><li><p>&Ouml;ffnen Sie auf dem Android-Ger&auml;t die <span class="guimenu">Einstellungen</span>, Reiter
                    <span class="guisubmenu">Konten</span> und w&auml;hlen <span class="guimenuitem">Konto
                    hinzuf&uuml;gen</span>. Der Typ des hinzuzuf&uuml;genden Kontos ist
                    <span class="guimenuitem">Microsoft Exchange ActiveSync</span>.</p><div class="informaltable"><table border="0"><colgroup><col><col></colgroup><tbody><tr><td align="center">
                                <div class="mediaobject"><img src="../images/webgroupware/activesync-android-account01.png"></div>
                            </td><td align="center">
                                <div class="mediaobject"><img src="../images/webgroupware/activesync-android-account02.png"></div>
                            </td></tr></tbody></table></div></li><li><p>Geben Sie Ihre E-Mail-Adresse und das Passwort des Benutzerkontos auf dem
                Intranator Server ein. W&auml;hlen Sie dann <span class="guimenuitem">Manuelles
                    Einrichten</span>.</p><div class="mediaobject"><img src="../images/webgroupware/activesync-android-account03.png"></div></li><li><p> Tragen Sie unter <span class="guimenuitem">Dom&auml;ne/Benutzername</span> einen
                    <strong class="userinput"><code>\</code></strong> (<span class="foreignphrase"><em class="foreignphrase">Backslash</em></span>) direkt
                gefolgt vom Benutzernamen auf dem Intranator ein. Tragen Sie im Feld
                    <span class="guimenuitem">Exchange Server</span> den externen DNS-Namen des
                Intranators ein. Die Option <span class="guimenuitem">Sichere Verbindung (SSL)</span> muss
                aktiviert sein. </p><div class="mediaobject"><img src="../images/webgroupware/activesync-android-account04.png"></div></li><li><p>Wird kein Zertifikat einer offiziellen Zertifizierungsstelle verwendet, erscheint
                nun eine Sicherheitswarnung. Da Sie ja sichergestellt haben, dass der vollst&auml;ndige
                Verbindungsweg zwischen Android-Ger&auml;t und Intranator Server vertrauensw&uuml;rdig ist,
                handelt es sich nicht um ein gef&auml;lschtes Zertifikat. Sie k&ouml;nnen daher an dieser
                Stelle auf <span class="guibutton">Weiter</span> gehen und das Zertifikat damit dauerhaft im
                Ger&auml;t als vertrauensw&uuml;rdig speichern.</p><p>Wird das Zertifikat einer offiziellen Zertifizierungsstelle verwendet, darf eine
                solche Sicherheitswarnung nicht erscheinen. Tut sie es dennoch, gehen Sie auf keinen
                Fall auf <span class="guibutton">Weiter</span>, sondern &uuml;berpr&uuml;fen als erstes die
                Konfiguration auf dem Server und versuchen es dann &uuml;ber einen anderen Verbindungsweg
                erneut.</p><div class="mediaobject"><img src="../images/webgroupware/activesync-android-account05.png"></div></li><li><p>Als n&auml;chstes wird konfiguriert, wie h&auml;ufig Daten zwischen Server und Mobilger&auml;t
                synchronisiert werden sollen. Android bietet hier die M&ouml;glichkeit zwischen den
                normalen <span class="guimenuitem">Abrufeinstellungen</span> und
                    <span class="guimenuitem">Spitzenzeit</span> zu unterscheiden. Die Spitzenzeit ist
                dabei f&uuml;r die Kernarbeitszeit vorgesehen und kann sp&auml;ter genau auf Stunden und
                Wochentage eingestellt werden.</p><div class="tip" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Tip"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Tipp]" src="../images/admon/tip.png"></td><th align="left">Tipp</th></tr><tr><td align="left" valign="top"><p>Wir empfehlen die &Uuml;bertragungsh&auml;ufigkeit auf 15 Minuten oder mehr zu stellen
                    und raten von der Verwendung von <span class="guimenuitem">Push</span> ab. Im
                    Push-Modus ist st&auml;ndig eine Funkverbindung aktiv und das Ger&auml;t kann daher kaum
                    noch Gebrauch von seinen Energiesparmodi machen. Dadurch sinkt die
                    Batteriereichweite signifikant. Au&szlig;erdem haben wir bei einigen Ger&auml;ten im
                    Push-Modus &Uuml;bertragungsfehler beobachtet, die zu einer Verdoppelung von E-Mails
                    und Terminen f&uuml;hren.</p></td></tr></table></div><p>Au&szlig;erdem kann konfiguriert werden, dass nur die E-Mails und Kalendereintr&auml;ge eines
                bestimmten Zeitraums &uuml;bertragen werden. Dies spart &Uuml;bertragungsvolumen,
                Speicherplatz auf dem Mobilger&auml;t und l&auml;sst die Anwendungen auf dem Mobilger&auml;t nicht
                tr&auml;ge werden.</p><p>Im unteren Bereich des Dialogs kann ausgew&auml;hlt werden, welche Objekttypen
                synchronisiert werden sollen. Der Intranator Server bietet keine Synchronisation von
                SMS an, deaktivieren Sie diese daher.</p><div class="informaltable"><table border="0"><colgroup><col><col></colgroup><tbody><tr><td align="center">
                                <div class="mediaobject"><img src="../images/webgroupware/activesync-android-account06.png"></div>
                            </td><td align="center">
                                <div class="mediaobject"><img src="../images/webgroupware/activesync-android-account07.png"></div>
                            </td></tr></tbody></table></div></li><li><p>Geben Sie dem Konto als Letztes einen aussagekr&auml;ftigen Namen. Dieser wird in den
                verschiedenen Applikationen bei der Auswahl zwischen den verschiedenen Konten
                angezeigt.</p><div class="mediaobject"><img src="../images/webgroupware/activesync-android-account08.png"></div></li></ol></div><p>Das neue Konto wird nun bei E-Mails, den Kontakten und Terminen/Aufgaben in den
        entsprechenden Applikationen zur Auswahl angeboten. Bei neu anzulegenden Objekten besteht
        die M&ouml;glichkeit, zwischen den verschiedenen auf dem Ger&auml;t eingerichteten Konten zu
        w&auml;hlen.</p><p>Alle betroffenen Applikationen bieten auch die M&ouml;glichkeit, manuell eine Synchronisation
        der Daten auszul&ouml;sen. Diese M&ouml;glichkeit ist einem sehr kurzen Synchronisationsintervall
        typischerweise vorzuziehen.</p></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="webgroupware-activesync-tips.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="webgroupware.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="webgroupware-activesync-ios.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">29.3. Besonderheiten und Tipps&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;31. Kapitel - ActiveSync mit Apple iOS-Ger&auml;ten</td></tr></table></div>
      
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